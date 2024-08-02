#include "MyTest.h"
#include "Address.pb.h"
#include "Person.pb.h"
//using namespace Dabing;
//using namespace Erbing;

void MyTest::test()
{
    // 序列化
    MMR::Person p;
    p.set_id(10);
    p.set_age(32);
    p.set_sex("man");

    p.add_name();
    p.set_name(0,u8"lufei");
    p.add_name(u8"aisi");
    p.add_name(u8"sabo");
    p.mutable_addr()->set_addr(u8"beijingtiananmen");
    p.mutable_addr()->set_num(1001);
    p.set_color(MMR::Color::Blue);

    // 序列化对象 p, 最终得到一个字符串
    std::string output;
	p.SerializeToString(&output);

	int32_t lOutLen = p.ByteSize();
	char* outArr = new char[lOutLen];
    p.SerializeToArray(outArr, lOutLen);

    // 反序列化数据
	MMR::Person pp;
    pp.ParseFromArray(outArr, lOutLen);
    std::cout << pp.id()  << ", " << pp.sex() << ", " << pp.age() << std::endl;
    std::cout << pp.addr().addr() << ", " << pp.addr().num() << std::endl;
    int size = pp.name_size();
    for(int i=0; i<size; ++i)
    {
        std::cout << pp.name(i) << std::endl;
    }
    std::cout << pp.color() << std::endl;
}

