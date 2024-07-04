#ifndef CMATRIX_H
#define CMATRIX_H
#include "Common_def.h"
#include "util/UtilExport.h"
#include <string>

BEGINE_NAMESPACE(mmrUtil)


template<class _Ty>
class COMMON_CLASS_API CMatrix {
public:
	CMatrix();

	CMatrix(const size_t nRow, const size_t nCol);

	/*explicit */CMatrix(const CMatrix<_Ty> &rhs);//�������캯��

	CMatrix(CMatrix<_Ty>&& rhs) noexcept;//�ƶ����캯��

	~CMatrix();

	const size_t getRowCount() const { return m_rows; }

	const size_t getColCount() const { return m_cols; }

	void reSizeArray(const size_t nRow, const size_t nCol);

	bool zeroArray();

	_Ty* operator[](const size_t index);

	const _Ty* operator[] (const size_t index) const;

	CMatrix<_Ty>& operator=(const _Ty& value);

	CMatrix<_Ty>& operator=(const CMatrix<_Ty> &rhs);

	CMatrix<_Ty>& operator=(CMatrix<_Ty>&& rhs) noexcept;

	//template<typename _Ty>
	//friend std::ostream& operator<< (std::ostream &os, const CMatrix<_Ty>& rhs);

	bool operator==(const CMatrix<_Ty> &rhs);

	bool operator!=(const CMatrix<_Ty> &rhs);

	_Ty** getPtr() { return m_array; }
private:
	bool isBuildInDataType();

	void destroyArray();
private:
	size_t m_rows;
	size_t m_cols;
	_Ty** m_array;
};

#define INSTANTIATE_TYPE_CLASS(type) \
template class COMMON_CLASS_API CMatrix<type>; \
//template std::ostream &operator<<(std::ostream &os, const CMatrix<type>& rhs);

INSTANTIATE_TYPE_CLASS(bool)
INSTANTIATE_TYPE_CLASS(uint8_t)
INSTANTIATE_TYPE_CLASS(int8_t)
INSTANTIATE_TYPE_CLASS(uint16_t)
INSTANTIATE_TYPE_CLASS(int16_t)
INSTANTIATE_TYPE_CLASS(uint32_t)
INSTANTIATE_TYPE_CLASS(int32_t)
INSTANTIATE_TYPE_CLASS(uint64_t)
INSTANTIATE_TYPE_CLASS(int64_t)
INSTANTIATE_TYPE_CLASS(float)
INSTANTIATE_TYPE_CLASS(double)

//INSTANTIATE_TYPE_CLASS(char*)//��Ҫ�ػ�
INSTANTIATE_TYPE_CLASS(std::string)

END_NAMESPACE(mmrUtil)

#endif
