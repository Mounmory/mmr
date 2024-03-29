
#ifndef JSON_HPP
#define JSON_HPP


#include "Common.h"
#include "util/UtilCommon.h"

#include <cstdint>
#include <cmath>
#include <cctype>
#include <string>
#include <deque>
#include <map>
#include <type_traits>
#include <initializer_list>
#include <ostream>
#include <iostream>

BEGINE_NAMESPACE(MmrCommon)

using std::map;
using std::deque;
using std::string;
using std::enable_if;
using std::initializer_list;
using std::is_same;
using std::is_convertible;
using std::is_integral;
using std::is_floating_point;

namespace {
	string json_escape(const string &str) {
		string output;
		output.reserve(str.capacity());
		for (const auto iter :str)
			switch (iter) {
			case '\"': output += "\\\""; break;
			case '\\': output += "\\\\"; break;
			case '\b': output += "\\b";  break;
			case '\f': output += "\\f";  break;
			case '\n': output += "\\n";  break;
			case '\r': output += "\\r";  break;
			case '\t': output += "\\t";  break;
			default: output += iter; break;
			}
		return std::move(output);
	}
}

class JSON
{
	union BackingData {
		BackingData(double d) : Float(d) {}
		BackingData(long   l) : Int(l) {}
		BackingData(bool   b) : Bool(b) {}
		BackingData(string s) : String(new string(std::move(s))) {}
		BackingData() : Int(0) {}

		deque<JSON>        *List;
		map<string, JSON>   *Map;
		string             *String;
		double              Float;
		long                Int;
		bool                Bool;
	} ;

	//internal data
	BackingData Internal;
public:
	enum class emJsonType {
		Null,
		Object,
		Array,
		String,
		Floating,
		Integral,
		Boolean
	};

	template <typename Container>
	class JSONWrapper {
		Container *object;

	public:
		JSONWrapper(Container *val) : object(val) {}
		JSONWrapper(std::nullptr_t) : object(nullptr) {}

		typename Container::iterator begin() { return object ? object->begin() : typename Container::iterator(); }
		typename Container::iterator end() { return object ? object->end() : typename Container::iterator(); }
		typename Container::const_iterator begin() const { return object ? object->begin() : typename Container::iterator(); }
		typename Container::const_iterator end() const { return object ? object->end() : typename Container::iterator(); }
	};

	template <typename Container>
	class JSONConstWrapper {
		const Container *object;

	public:
		JSONConstWrapper(const Container *val) : object(val) {}
		JSONConstWrapper(std::nullptr_t) : object(nullptr) {}

		typename Container::const_iterator begin() const { return object ? object->begin() : typename Container::const_iterator(); }
		typename Container::const_iterator end() const { return object ? object->end() : typename Container::const_iterator(); }
	};

	JSON() : Internal(), Type(emJsonType::Null) {}

	JSON(initializer_list<JSON> list)
		: JSON()
	{
		SetType(emJsonType::Object);
		for (auto i = list.begin(), e = list.end(); i != e; ++i, ++i)
			operator[](i->ToString()) = *std::next(i);
	}

	JSON(JSON&& other)
		: Internal(other.Internal)
		, Type(other.Type)
	{
		other.Type = emJsonType::Null; other.Internal.Map = nullptr;
	}

	JSON& operator=(JSON&& other) {
		ClearInternal();
		Internal = other.Internal;
		Type = other.Type;
		other.Internal.Map = nullptr;
		other.Type = emJsonType::Null;
		return *this;
	}

	JSON(const JSON &other) {
		switch (other.Type) {
		case emJsonType::Object:
			Internal.Map =
				new map<string, JSON>(other.Internal.Map->begin(),
					other.Internal.Map->end());
			break;
		case emJsonType::Array:
			Internal.List =
				new deque<JSON>(other.Internal.List->begin(),
					other.Internal.List->end());
			break;
		case emJsonType::String:
			Internal.String =
				new string(*other.Internal.String);
			break;
		default:
			Internal = other.Internal;
		}
		Type = other.Type;
	}

	JSON& operator=(const JSON &other) {
		ClearInternal();
		switch (other.Type) {
		case emJsonType::Object:
			Internal.Map =
				new map<string, JSON>(other.Internal.Map->begin(),
					other.Internal.Map->end());
			break;
		case emJsonType::Array:
			Internal.List =
				new deque<JSON>(other.Internal.List->begin(),
					other.Internal.List->end());
			break;
		case emJsonType::String:
			Internal.String =
				new string(*other.Internal.String);
			break;
		default:
			Internal = other.Internal;
		}
		Type = other.Type;
		return *this;
	}

	~JSON() {
		switch (Type) {
		case emJsonType::Array:
			delete Internal.List;
			break;
		case emJsonType::Object:
			delete Internal.Map;
			break;
		case emJsonType::String:
			delete Internal.String;
			break;
		default:;
		}
	}

	template <typename T>
	JSON(T b, typename enable_if<is_same<T, bool>::value>::type* = 0) : Internal(b), Type(emJsonType::Boolean) {}

	template <typename T>
	JSON(T i, typename enable_if<is_integral<T>::value && !is_same<T, bool>::value>::type* = 0) : Internal((long)i), Type(emJsonType::Integral) {}

	template <typename T>
	JSON(T f, typename enable_if<is_floating_point<T>::value>::type* = 0) : Internal((double)f), Type(emJsonType::Floating) {}

	template <typename T>
	JSON(T s, typename enable_if<is_convertible<T, string>::value>::type* = 0) : Internal(string(s)), Type(emJsonType::String) {}

	JSON(std::nullptr_t) : Internal(), Type(emJsonType::Null) {}

	static JSON Make(emJsonType type) {
		JSON ret; ret.SetType(type);
		return ret;
	}

	static JSON Load(const string &);

	template <typename T>
	void append(T arg) {
		SetType(emJsonType::Array); Internal.List->emplace_back(arg);
	}

	template <typename T, typename... U>
	void append(T arg, U... args) {
		append(arg); append(args...);
	}

	template <typename T>
	typename enable_if<is_same<T, bool>::value, JSON&>::type operator=(T b) {
		SetType(emJsonType::Boolean); Internal.Bool = b; return *this;
	}

	template <typename T>
	typename enable_if<is_integral<T>::value && !is_same<T, bool>::value, JSON&>::type operator=(T i) {
		SetType(emJsonType::Integral); Internal.Int = i; return *this;
	}

	template <typename T>
	typename enable_if<is_floating_point<T>::value, JSON&>::type operator=(T f) {
		SetType(emJsonType::Floating); Internal.Float = f; return *this;
	}

	template <typename T>
	typename enable_if<is_convertible<T, string>::value, JSON&>::type operator=(T s) {
		SetType(emJsonType::String); *Internal.String = string(s); return *this;
	}

	JSON& operator[](const string &key) {
		SetType(emJsonType::Object); return Internal.Map->operator[](key);
	}

	JSON& operator[](unsigned index) {
		SetType(emJsonType::Array);
		if (index >= Internal.List->size()) Internal.List->resize(index + 1);
		return Internal.List->operator[](index);
	}

	JSON &at(const string &key) {
		return operator[](key);
	}

	const JSON &at(const string &key) const {
		return Internal.Map->at(key);
	}

	JSON &at(unsigned index) {
		return operator[](index);
	}

	const JSON &at(unsigned index) const {
		return Internal.List->at(index);
	}

	int length() const {
		if (Type == emJsonType::Array)
			return Internal.List->size();
		else
			return -1;
	}

	bool hasKey(const string &key) const {
		if (Type == emJsonType::Object)
			return Internal.Map->find(key) != Internal.Map->end();
		return false;
	}

	int size() const {
		if (Type == emJsonType::Object)
			return Internal.Map->size();
		else if (Type == emJsonType::Array)
			return Internal.List->size();
		else
			return -1;
	}

	emJsonType JSONType() const { return Type; }

	/// Functions for getting primitives from the JSON object.
	bool IsNull() const { return Type == emJsonType::Null; }

	string ToString() const { bool b; return std::move(ToString(b)); }
	string ToString(bool &ok) const {
		ok = (Type == emJsonType::String);
		return ok ? std::move(json_escape(*Internal.String)) : string("");
	}

	double ToFloat() const { bool b; return ToFloat(b); }
	double ToFloat(bool &ok) const {
		ok = (Type == emJsonType::Floating);
		return ok ? Internal.Float : 0.0;
	}

	long ToInt() const { bool b; return ToInt(b); }
	long ToInt(bool &ok) const {
		ok = (Type == emJsonType::Integral);
		return ok ? Internal.Int : 0;
	}

	bool ToBool() const { bool b; return ToBool(b); }
	bool ToBool(bool &ok) const {
		ok = (Type == emJsonType::Boolean);
		return ok ? Internal.Bool : false;
	}

	JSONWrapper<map<string, JSON>> ObjectRange() {
		if (Type == emJsonType::Object)
			return JSONWrapper<map<string, JSON>>(Internal.Map);
		return JSONWrapper<map<string, JSON>>(nullptr);
	}

	JSONWrapper<deque<JSON>> ArrayRange() {
		if (Type == emJsonType::Array)
			return JSONWrapper<deque<JSON>>(Internal.List);
		return JSONWrapper<deque<JSON>>(nullptr);
	}

	JSONConstWrapper<map<string, JSON>> ObjectRange() const {
		if (Type == emJsonType::Object)
			return JSONConstWrapper<map<string, JSON>>(Internal.Map);
		return JSONConstWrapper<map<string, JSON>>(nullptr);
	}


	JSONConstWrapper<deque<JSON>> ArrayRange() const {
		if (Type == emJsonType::Array)
			return JSONConstWrapper<deque<JSON>>(Internal.List);
		return JSONConstWrapper<deque<JSON>>(nullptr);
	}

	string dump(int depth = 1, string tab = "  ") const {
		string pad = "";
		for (int i = 0; i < depth; ++i, pad += tab);

		switch (Type) {
		case emJsonType::Null:
			return "null";
		case emJsonType::Object: {
			string s = "{\n";
			bool skip = true;
			for (auto &p : *Internal.Map) {
				if (!skip) s += ",\n";
				s += (pad + "\"" + p.first + "\" : " + p.second.dump(depth + 1, tab));
				skip = false;
			}
			s += ("\n" + pad.erase(0, 2) + "}");
			return s;
		}
		case emJsonType::Array: {
			string s = "[";
			bool skip = true;
			for (auto &p : *Internal.List) {
				if (!skip) s += ", ";
				s += p.dump(depth + 1, tab);
				skip = false;
			}
			s += "]";
			return s;
		}
		case emJsonType::String:
			return "\"" + json_escape(*Internal.String) + "\"";
		case emJsonType::Floating:
			return std::to_string(Internal.Float);
		case emJsonType::Integral:
			return std::to_string(Internal.Int);
		case emJsonType::Boolean:
			return Internal.Bool ? "true" : "false";
		default:
			return "";
		}
		return "";
	}

	friend std::ostream& operator<<(std::ostream&, const JSON &);

private:
	void SetType(emJsonType type) {
		if (type == Type)
			return;

		ClearInternal();

		switch (type) {
		case emJsonType::Null:      Internal.Map = nullptr;                break;
		case emJsonType::Object:    Internal.Map = new map<string, JSON>(); break;
		case emJsonType::Array:     Internal.List = new deque<JSON>();     break;
		case emJsonType::String:    Internal.String = new string();           break;
		case emJsonType::Floating:  Internal.Float = 0.0;                    break;
		case emJsonType::Integral:  Internal.Int = 0;                      break;
		case emJsonType::Boolean:   Internal.Bool = false;                  break;
		}

		Type = type;
	}

private:
	/* beware: only call if YOU know that Internal is allocated. No checks performed here.
	This function should be called in a constructed JSON just before you are going to
	overwrite Internal...
	*/
	void ClearInternal() {
		switch (Type) {
		case emJsonType::Object: delete Internal.Map;    break;
		case emJsonType::Array:  delete Internal.List;   break;
		case emJsonType::String: delete Internal.String; break;
		default:;
		}
	}

private:

	emJsonType Type = emJsonType::Null;
};

JSON Array() {
	return std::move(JSON::Make(JSON::emJsonType::Array));
}

template <typename... T>
JSON Array(T... args) {
	JSON arr = JSON::Make(JSON::emJsonType::Array);
	arr.append(args...);
	return std::move(arr);
}

JSON Object() {
	return std::move(JSON::Make(JSON::emJsonType::Object));
}

std::ostream& operator<<(std::ostream &os, const JSON &json) {
	os << json.dump();
	return os;
}

namespace {
	JSON parse_next(const string &, size_t &);

	void consume_ws(const string &str, size_t &offset) {
		while (isspace(str[offset])) ++offset;
	}

	JSON parse_object(const string &str, size_t &offset) {
		JSON Object = JSON::Make(JSON::emJsonType::Object);

		++offset;
		consume_ws(str, offset);
		if (str[offset] == '}') {
			++offset; return std::move(Object);
		}

		while (true) {
			JSON Key = parse_next(str, offset);
			consume_ws(str, offset);
			if (str[offset] != ':') {
				std::cerr << "Error: Object: Expected colon, found '" << str[offset] << "'\n";
				break;
			}
			consume_ws(str, ++offset);
			JSON Value = parse_next(str, offset);
			Object[Key.ToString()] = Value;

			consume_ws(str, offset);
			if (str[offset] == ',') {
				++offset; continue;
			}
			else if (str[offset] == '}') {
				++offset; break;
			}
			else {
				std::cerr << "ERROR: Object: Expected comma, found '" << str[offset] << "'\n";
				break;
			}
		}

		return std::move(Object);
	}

	JSON parse_array(const string &str, size_t &offset) {
		JSON Array = JSON::Make(JSON::emJsonType::Array);
		unsigned index = 0;

		++offset;
		consume_ws(str, offset);
		if (str[offset] == ']') {
			++offset; return std::move(Array);
		}

		while (true) {
			Array[index++] = parse_next(str, offset);
			consume_ws(str, offset);

			if (str[offset] == ',') {
				++offset; continue;
			}
			else if (str[offset] == ']') {
				++offset; break;
			}
			else {
				std::cerr << "ERROR: Array: Expected ',' or ']', found '" << str[offset] << "'\n";
				return std::move(JSON::Make(JSON::emJsonType::Array));
			}
		}

		return std::move(Array);
	}

	JSON parse_string(const string &str, size_t &offset) {
		JSON String;
		string val;
		for (char c = str[++offset]; c != '\"'; c = str[++offset]) {
			if (c == '\\') {
				switch (str[++offset]) {
				case '\"': val += '\"'; break;
				case '\\': val += '\\'; break;
				case '/': val += '/'; break;
				case 'b': val += '\b'; break;
				case 'f': val += '\f'; break;
				case 'n': val += '\n'; break;
				case 'r': val += '\r'; break;
				case 't': val += '\t'; break;
				case 'u': {
					val += "\\u";
					for (unsigned i = 1; i <= 4; ++i) {
						c = str[offset + i];
						if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
							val += c;
						else {
							std::cerr << "ERROR: String: Expected hex character in unicode escape, found '" << c << "'\n";
							return std::move(JSON::Make(JSON::emJsonType::String));
						}
					}
					offset += 4;
				} break;
				default: val += '\\'; break;
				}
			}
			else
				val += c;
		}
		++offset;
		String = val;
		return std::move(String);
	}

	JSON parse_number(const string &str, size_t &offset) {
		JSON Number;
		string val, exp_str;
		char c;
		bool isDouble = false;
		long exp = 0;
		while (true) {
			c = str[offset++];
			if ((c == '-') || (c >= '0' && c <= '9'))
				val += c;
			else if (c == '.') {
				val += c;
				isDouble = true;
			}
			else
				break;
		}
		if (c == 'E' || c == 'e') {
			c = str[offset++];
			if (c == '-') { ++offset; exp_str += '-'; }
			while (true) {
				c = str[offset++];
				if (c >= '0' && c <= '9')
					exp_str += c;
				else if (!isspace(c) && c != ',' && c != ']' && c != '}') {
					std::cerr << "ERROR: Number: Expected a number for exponent, found '" << c << "'\n";
					return std::move(JSON::Make(JSON::emJsonType::Null));
				}
				else
					break;
			}
			exp = std::stol(exp_str);
		}
		else if (!isspace(c) && c != ',' && c != ']' && c != '}') {
			std::cerr << "ERROR: Number: unexpected character '" << c << "'\n";
			return std::move(JSON::Make(JSON::emJsonType::Null));
		}
		--offset;

		if (isDouble)
			Number = std::stod(val) * std::pow(10, exp);
		else {
			if (!exp_str.empty())
				Number = std::stol(val) * std::pow(10, exp);
			else
				Number = std::stol(val);
		}
		return std::move(Number);
	}

	JSON parse_bool(const string &str, size_t &offset) {
		JSON Bool;
		if (str.substr(offset, 4) == "true")
			Bool = true;
		else if (str.substr(offset, 5) == "false")
			Bool = false;
		else {
			std::cerr << "ERROR: Bool: Expected 'true' or 'false', found '" << str.substr(offset, 5) << "'\n";
			return std::move(JSON::Make(JSON::emJsonType::Null));
		}
		offset += (Bool.ToBool() ? 4 : 5);
		return std::move(Bool);
	}

	JSON parse_null(const string &str, size_t &offset) {
		JSON Null;
		if (str.substr(offset, 4) != "null") {
			std::cerr << "ERROR: Null: Expected 'null', found '" << str.substr(offset, 4) << "'\n";
			return std::move(JSON::Make(JSON::emJsonType::Null));
		}
		offset += 4;
		return std::move(Null);
	}

	JSON parse_next(const string &str, size_t &offset) {
		char value;
		consume_ws(str, offset);
		value = str[offset];
		switch (value) {
		case '[': return std::move(parse_array(str, offset));
		case '{': return std::move(parse_object(str, offset));
		case '\"': return std::move(parse_string(str, offset));
		case 't':
		case 'f': return std::move(parse_bool(str, offset));
		case 'n': return std::move(parse_null(str, offset));
		default: if ((value <= '9' && value >= '0') || value == '-')
			return std::move(parse_number(str, offset));
		}
		std::cerr << "ERROR: Parse: Unknown starting character '" << value << "'\n";
		return JSON();
	}
}

JSON JSON::Load(const string &str) {
	size_t offset = 0;
	return std::move(parse_next(str, offset));
}

END_NAMESPACE(MmrCommon)




#endif // !JSON_HPP
