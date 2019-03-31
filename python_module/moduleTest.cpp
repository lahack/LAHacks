#include <string>
#include <vector>

#include "Language.h"

using namespace std;

int main() {
    string text = "Google, headquartered in Mountain View, unveiled the new Android phone at the Consumer Electronic Show.  Sundar Pichai said in his keynote that users love their new Android phones.";
    vector<string> vec(3, "test");

    Language lang("/Users/lihanzhu/Desktop/lahacks/Cloud/service-account.json");

    lang.checkEntities(text, vec);

    return 0;
}