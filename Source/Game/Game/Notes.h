#pragma once

//template <typename T>
//void print(const std::string& s, const T& container)
//{
//	std::cout << s << std::endl;
//		for (auto element : container)
//		{
//			std::cout << element << " ";
//		}
//	std::cout << std::endl;
//}

//void print_arg(int count, ...)
//{
//	va_list args;
//
//	va_start(args, count);
//	for (int i = 0; i < count; ++i)
//	{
//		std::cout << va_arg(args, const char*) << std::endl;
//	}
//
//	va_end(args);
//}



//void zero(int v)
//{
//	v = 0;
//}
//
//void zero(int* v)
//{
//	*v = 0; // set address to 0, but we want to set address of thing in parameter, we do this by dereferencing *v
//}
//
//void zero_ref(const int& v) //with const we CANNOT change the value of v
//{
//	//v = 0; // dont need to dereference
//}
//
//void print(const std::string& s)
//{
//	cout << s << endl;
//}
//
//void print(std::vector<int> v)
//{
//
//}

//main
	//int i = 5;
	////zero(&i); // pass in address of value, explicit
	//zero_ref(5); // cannot pass literal value unless const
	//cout << i << endl;
	//print("hello world");

	//std::vector<int> vec;
	//vec.resize(10000); // vec = 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	//print(vec);


	//rapidjson::Document document;
	//kiko::Json::Load("json.txt", document);

	//int i1;
	//kiko::Json::Read(document, "integer1", i1);
	//std::cout << i1 << std::endl;

	//int i2;
	//kiko::Json::Read(document, "integer2", i2);
	//std::cout << i2 << std::endl;

	//std::string str;
	//kiko::Json::Read(document, "string", str);
	//std::cout << str << std::endl;

	//bool b;
	//kiko::Json::Read(document, "boolean", b);
	//std::cout << b << std::endl;

	//float f;
	//kiko::Json::Read(document, "float", f);
	//std::cout << f << std::endl;

	//kiko::vec2 v2;
	//kiko::Json::Read(document, "vector2", v2, false);
	//std::cout << v2 << std::endl;



//auto actor = INSTANTIATE(Actor, "Crate");
//actor->transform.position = { kiko::random(kiko::g_renderer.GetWidth()), 100 };
//actor->Initialize();
//m_scene->Add(std::move(actor));

//camera.x = (int)(m_scene->GetActorByName("Player")->transform.position.x - 400);
//camera.y = (int)(m_scene->GetActorByName("Player")->transform.position.y - 300);

//if (camera.x < 0) camera.x = 0;
//if (camera.y < 0) camera.y = 0;
//if (camera.x > camera.w) camera.x = camera.w;
//if (camera.y > camera.h) camera.y = camera.h;