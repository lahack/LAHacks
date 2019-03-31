#include <Python/Python.h>
#include <iostream>

#include "Language.h"

using namespace std;

Language::Language(string keyPath) {
    credentialPath = keyPath;
}

bool Language::checkEntities(string text, vector<string> entities) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pText, *pArgs, *pValue;

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");

    pName = PyString_FromString("LangCall");
    pText = PyString_FromString(text.c_str());

    if (!pText) {
        fprintf(stderr, "Cannot convert argument\n");
        return false;
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "checkEntities");

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);  // Argument list

            // First argument: keyPath
            pValue = PyString_FromString(credentialPath.c_str());
            PyTuple_SetItem(pArgs, 0, pValue);

            // Second argument: text
            PyTuple_SetItem(pArgs, 1, pText);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            // Compare
            if (pValue != NULL) {
                vector<string> result;
                PyObject *pItem;

                for (int i = 0; i < PyTuple_Size(pValue); i++) {
                    pItem = PyTuple_GetItem(pValue, i);

                    const char* tempCStr = PyString_AsString(pItem);
                    string tempStr = tempCStr;
                    result.push_back(tempStr);
                }

                Py_DECREF(pItem);

                cout << "Result of call:\n";
                for (int i = 0; i < result.size(); i++) {
                    cout << result[i] << endl;
                }
                Py_DECREF(pValue);

                return true;

                //printf("Result of call: %ld\n", PyInt_AsLong(pValue));
            }
        }
    }

    return false;
}