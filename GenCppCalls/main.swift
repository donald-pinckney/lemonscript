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
        return "\(self)".uppercaseString
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

        typedefs += "typedef bool(*\(typeName))(\(commaList));\n"
        
        if numParams == 0 {
            body += "\tif(vector<DataType>{\(COMMAList)} == params) {\n"
        } else {
            body += "\telse if(vector<DataType>{\(COMMAList)} == params) {\n"
        }
        body += "\t\t\(typeName) tempFunc = (\(typeName))func;\n"
        body += "\t\tretVal = tempFunc(\n"
        
        var pCount = 0
        for p in params {
            let name = p.cppName()
            
            if(pCount == params.count - 1) {
                body += "\t\t\tisArgumentLiteral[\(pCount)] ? *((\(name) *)&parameterValues[\(pCount)]) : *((\(name) *)parameterValues[\(pCount)])\n"
            } else {
                body += "\t\t\tisArgumentLiteral[\(pCount)] ? *((\(name) *)&parameterValues[\(pCount)]) : *((\(name) *)parameterValues[\(pCount)]),\n"
            }
            
            pCount += 1
        }
        
        body += "\t\t\t);\n\t}\n\n"
        
        
        // Next parameter combination
        for incrementIndex in ReverseCollection(0..<numParams) {
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
print("bool CppCommand::Update() {\n\tvoid *func = declaration->func;\n\tvector<DataType> params = declaration->parameters;\n\tbool retVal;\n")
print(body)
print("\telse {\n\t\tthrow \"Too many arguments!\";\n\t}\n\treturn retVal;\n}")
print("#endif /* CppCommand_GENERATED_h */")

