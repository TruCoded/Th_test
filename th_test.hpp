#ifndef TH_TEST_
#define TH_TEST_

#include <vector>
#include <iostream>

using namespace std;

#define TEST(func_name)\
    void func_name();\
    struct func_name##registrer{\
        func_name##registrer(){\
            TH_TEST::tests.push_back({&func_name, #func_name,__FILE__,__LINE__});\
        }\
    };\
    struct func_name##registrer func_name##registrer_instance; 

#define ASSERT(condition)\
{\
    if(!(condition)){\
        cout<<"[" #condition " Failed at: " __FILE__ ":" <<__LINE__ <<"]"<<endl;\
        TH_TEST::current_test->passed=false;\
    }\
}

namespace TH_TEST {

    struct test_function{
        void(*func)() ;
        const char* name;
        const char* file;
        int line;
        bool passed=true;
    };
    inline vector<struct test_function> tests;

    inline struct test_function* current_test=nullptr;

    inline void RUN_TESTS(){
        cout << "RUNNING Tests..." << endl << endl;
        
        for(auto& test:tests){
            current_test=&test;
            test.func();
        }
        cout << endl;

        cout << "--------------------------Tests Report---------------------------------" << endl;
        
        int passed_count = 0;
        int total_tests = tests.size();
        
        for(size_t i = 0; i < tests.size(); ++i){
            cout << "\t[" << (i + 1) << "/" << total_tests << "] " << tests[i].name << "() ";
            if(tests[i].passed){
                cout << "[Passed]" << endl;
                passed_count++;
            }else{
                cout << "[Failed]" << endl;
            }
        }
        cout << endl;

        cout << "Passing Tests [" << passed_count << "/" << total_tests << "]" << endl;
    }

}

#endif
