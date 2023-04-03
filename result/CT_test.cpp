#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include "twomodule.h"
#include "linux/kernel.h"
#include "linux/module.h"
#include "rapidxml.hpp"
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#define DEBUG
using namespace rapidxml;
int main()
{
    long KBA1 = 0L;
    long KBA2 = 0L;
    long KBA3 = 0L;
    long KBA4 = 0L;
    long UST_overload = 0L;
    long UST_underloading = 0L;
    long UST = 0L;
    long RAB = 0L;

    std::map<std::string, long> map_k;
    std::map<std::string, bool> res;

    res["overload"] = false;
    res["underloading"] = false;
    res["two_overload"] = false;
    res["two_underloading"] = false;

    xml_document<> doc;
    xml_node<>* root_node = NULL;

    while (true)
    {
        root_node = NULL;
        std::ifstream theFile("input.xml");
        if (theFile.is_open())
        {
            std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            doc.parse<0>(&buffer[0]);
            root_node = doc.first_node("MyData");

            for (xml_node<>* var_node = root_node->first_node("VAR");
                var_node; var_node = var_node->next_sibling())
            {
                for (xml_node<>* var_value_node = var_node->first_node("Value"); var_value_node; var_value_node = var_value_node->next_sibling())
                {
                    std::string str = var_node->first_attribute("var_type")->value();
                    if (str == "KBA1" || str == "KBA2" || str == "KBA3" || str == "KBA4")
                    {
                        map_k[str] = std::stol(var_value_node->value());
                    }
                    else if (str == "UST_overload")
                    {
                        UST_overload = std::stol(var_value_node->value());
                    }
                    else if (str == "UST_underloading")
                    {
                        UST_underloading = std::stol(var_value_node->value());
                    }
                    else if (str == "UST")
                    {
                        UST = std::stol(var_value_node->value());
                    }
                    else if (str == "RAB")
                    {
                        RAB = std::stol(var_value_node->value());
                    }

                }

            }
            buffer.clear();
            root_node->remove_all_nodes();
            doc.clear();
            doc.remove_all_attributes();
            doc.remove_all_nodes();
            theFile.close();
            algor(res, map_k, UST_overload, UST_underloading, UST, RAB);
#ifdef DEBUG
            std::cout << "###############################################################################" << std::endl;
            std::cout << "UST_overload: " << UST_overload << std::endl;
            std::cout << "UST_underloading: " << UST_underloading << std::endl;
            std::cout << "UST: " << UST << std::endl;
            std::cout << "RAB: " << RAB << std::endl;
            for (auto& itr : map_k)
            {
                std::cout << itr.first << " " << itr.second << std::endl;
            }

            for (auto& itr : res)
            {
                std::cout << itr.first << " " << itr.second << std::endl;
            }
            std::cout << "###############################################################################" << std::endl;
#endif // DEBUG
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
        else
        {
            std::cout << "Error read file!" << std::endl;
            exit(-1);
        }
        
    }


}
