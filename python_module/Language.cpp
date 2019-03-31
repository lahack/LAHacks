#include <Python/Python.h>

#include "Language.h"

using namespace std;

Language::Language(string keyPath) {
    credentialPath = keyPath;
}

bool Language::checkEntities(string text, vector<string> entities) {

}