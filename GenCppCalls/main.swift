//
//  main.swift
//  GenCppCalls
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

import Foundation

enum DataType : Int {
    case int
    case float
    case boolean
    
    static func first() -> DataType {
        return int
    }
    
    func successor() -> DataType? {
        return DataType(rawValue: self.rawValue + 1)
    }
    
    func cppName() -> String {
        let ret = "\(self)"
        if ret == "boolean" {
            return "bool"
        }
        return ret
    }
    
    func meUpperName() -> String {
        return "DataType::" + "\(self)".uppercaseString
    }
}


// typedef bool(*f_float_int)(float, int);
var typedefs = ""

/*
 if(vector<DataType>{FLOAT, INT} == params) {
    f_float_int tempFunc = (f_float_int)func;
 
    retVal = tempFunc(
        isArgumentLiteral[0] ? *((float *)&parameterValues[0]) : *((float *)parameterValues[0]),
        isArgumentLiteral[1] ? *((int *)&parameterValues[1]) : *((int *)parameterValues[1])
        );
 }
 */

var body = ""

for numParams in 0...5 {
    var params = Array(count: numParams, repeatedValue: DataType.int)
    for _ in 0..<Int(pow(3, Float(numParams))) {
        
        let underscoreList = params.map { $0.cppName() }.joinWithSeparator("_")
        let commaList = params.map { $0.cppName() }.joinWithSeparator(", ")
        let COMMAList = params.map { $0.meUpperName() }.joinWithSeparator(", ")

        let typeName = "f_" + underscoreList

        
        if numParams == 0 {
            typedefs += "typedef bool(*\(typeName))(void *);\n"
            body += "\tif(vector<DataType>{\(COMMAList)} == params) {\n"
        } else {
            typedefs += "typedef bool(*\(typeName))(void *,\(commaList));\n"
            body += "\telse if(vector<DataType>{\(COMMAList)} == params) {\n"
        }
        
        
        body += "\t\t\(typeName) tempFunc = (\(typeName))func;\n"
        for i in 0..<params.count {
            let name = params[i].cppName()
            
            body += "\t\t\(name) p\(i);\n"
            body += "\t\tif(isArgumentLiteral[\(i)]) {\n\t\t\tp\(i) = *((\(name) *)&parameterValues[\(i)]);\n\t\t} else {\n\t\t\t((Expression *)parameterValues[\(i)])->getValue(&p\(i));\n\t\t}\n"
        }
        
        if numParams == 0 {
            body += "\t\tretVal = tempFunc(data"
        } else {
            body += "\t\tretVal = tempFunc(data, "
        }
        
        for i in 0..<params.count {
            
            if i == params.count - 1 {
                body += "p\(i)"
//                body += "\t\t\tisArgumentLiteral[\(pCount)] ? *((\(name) *)&parameterValues[\(pCount)]) : *((\(name) *)parameterValues[\(pCount)])\n"
            } else {
                body += "p\(i), "
//                body += "\t\t\tisArgumentLiteral[\(pCount)] ? *((\(name) *)&parameterValues[\(pCount)]) : *((\(name) *)parameterValues[\(pCount)]),\n"
            }
        }
        
        body += ");\n\t}\n\n"
        
        
        // Next parameter combination
        for incrementIndex in (0..<numParams).reverse() {
            if let next = params[incrementIndex].successor() {
                params[incrementIndex] = next
                break
            } else {
                params[incrementIndex] = DataType.first()
            }
        }
        
    }
    
}


/*
 bool CppCommand::Update() const {
    void *func = declaration->func;
    vector<DataType> params = declaration->parameters;
    bool retVal;

*/

/*
 
    return retVal;
 }
 */



print("#ifndef CppCommand_GENERATED_h\n#define CppCommand_GENERATED_h")
print(typedefs)
print("std::ofstream cppLog(\"lemonscript_cpp_calls.log\");\nbool lemonscript::CppCommand::Update() {\n\tvoid *data = savedState->userData;void *func = declaration->func;\n\tvector<DataType> params = declaration->parameters;\n\tbool retVal;\n\tcppLog << \"Calling C function: \" << declaration->functionName << std::endl;\n")
print(body)
print("\telse {\n\t\tthrow \"Too many arguments!\";\n\t}\n\treturn retVal;\n}")
print("#endif /* CppCommand_GENERATED_h */")

