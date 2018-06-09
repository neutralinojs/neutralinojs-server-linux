#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../lib/json/json.hpp"
#include "../settings.h"

using namespace std;
using json = nlohmann::json;

namespace filesystem {



    string createDirectory(string jso) {
        json input;
        json output;
        try {
            input = json::parse(jso);
        }
        catch(exception e){
            output["error"] = "JSON parse error is occurred!";
            return output.dump();
        }
        string filename = input["name"];
        if(mkdir(filename.c_str(), 0700) == 0){
            output["success"] = filename + " directory was created!";
            return output.dump();
        }
        else{
            output["error"] = "Cannot create " + filename;
            return output.dump();
        }
       
        
    }

    string removeDirectory(string jso) {
        json input;
        json output;
        try {
            input = json::parse(jso);
        }
        catch(exception e){
            output["error"] = "JSON parse error is occurred!";
            return output.dump();
        }
        string dir = input["dir"];
        if(rmdir(dir.c_str()) == 0){
            output["success"] = dir + " was removed.";
            return output.dump();
        }
        else{
            output["error"] = "Cannot remove " + dir;
            return output.dump();
        }   
    }

    string readFile(string jso) {
        json input;
        json output;
        try {
            input = json::parse(jso);
        }
        catch(exception e){
            output["error"] = "JSON parse error is occurred!";
            return output.dump();
        }
        string filename = input["filename"];
        output["content"] = settings::getFileContent(filename);
        return output.dump();
    }

     string writeFile(string jso) {
        json input;
        json output;
        try {
            input = json::parse(jso);
        }
        catch(exception e){
            output["error"] = "JSON parse error is occurred!";
            return output.dump();
        }
        string filename = input["filename"];
        string content = input["content"];
        ofstream t(filename);
        t << content;
        t.close();
        return output.dump();
    }   

    string removeFile(string jso) {
        json input;
        json output;
        try {
            input = json::parse(jso);
        }
        catch(exception e){
            output["error"] = "JSON parse error is occurred!";
            return output.dump();
        }
        string filename = input["filename"];
        if(remove(filename.c_str()) == 0){
            output["success"] = filename + " was removed.";
            return output.dump();
        }
        else{
            output["error"] = "Cannot remove " + filename;
            return output.dump();
        }   
    }
}
