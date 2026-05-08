#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "user.h"
#include "bst.h"
using namespace std;

// ======================== UTILITAS ========================

string roleStr(Role r);
bool semuaAngka(const string &s);
bool semuaAlphanumeric(const string &s);

// ======================== AUTH ========================

void login();

#endif