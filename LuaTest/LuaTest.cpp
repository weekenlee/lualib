// LuaTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <lua.hpp>
#include <string>

using std::cout;
using std::endl;

LUALIB_API int fun(lua_State *L) {
	if (L == nullptr) {
		return 0;
	}
	cout << "this is a message from cpp" << endl;
	return 0;
}

LUALIB_API int addandsub(lua_State *L) {
	if (L == nullptr) {
		return 0;
	}
	int n = lua_gettop(L);
	if (n != 2) {
		lua_pushstring(L, "参数错误");
		lua_error(L);
		return 0;
	}

	int first = luaL_checkinteger(L, -2);
	int second = luaL_checkinteger(L, -1);

	int add = first + second;
	int sub = first - second;

	lua_pushnumber(L, add);
	lua_pushnumber(L, sub);

	//返回参数个数
	return 2;
}



int main()
{
	lua_State *l = luaL_newstate();
	luaL_openlibs(l);

	int valueCPP = 1;
	lua_pushnumber(l, valueCPP);
	lua_setglobal(l, "valueCPP");
	lua_pushcfunction(l, fun);
	lua_setglobal(l, "fun");
	lua_pushcfunction(l, addandsub);
	lua_setglobal(l, "addandsub");
	luaL_dofile(l, "main.lua");
	lua_pop(l, 1);

	lua_getglobal(l, "a");
	if (!lua_isstring(l, -1)) {
		cout << "error" << endl;
	}
	cout << lua_tostring(l,-1) <<endl;
	lua_getglobal(l, "b");
	if (!lua_isstring(l, -1)) {
		cout << "error" << endl;
	}
	cout << lua_tostring(l, -2) << endl;
	cout << lua_tostring(l, -1) << endl;

	lua_pop(l, 2);

	lua_getglobal(l, "tworettwo");
	lua_pushinteger(l, 3);
	lua_pushinteger(l, 2);
	if (lua_pcall(l, 2, 2, 0) == 0) {
		int one = lua_tointeger(l, -1);
		int t = lua_tointeger(l, -2);
		cout << one << endl;
		cout << t << endl;
	}
	lua_pop(l, 2);

	lua_getglobal(l, "table");

	lua_pushstring(l, "a");
	lua_gettable(l, -2);
	if (lua_isinteger(l, -1)) {
		cout << "table.a= " << lua_tointeger(l, -1) << endl;

	}
	lua_pop(l, 1);

	lua_pushstring(l, "b");
	lua_gettable(l, -2);
	if (lua_isinteger(l, -1)) {
		cout << "table.b= " << lua_tointeger(l, -1) << endl;

	}
	lua_pop(l, 2);
	
	//遍历table
	lua_getglobal(l, "table");
	lua_pushnil(l);
	while (lua_next(l, -2))
	{
		//这时值在-1（栈顶）处，key在-2处。 
		cout << "table."<< lua_tostring(l, -2) <<"= " << lua_tointeger(l, -1) << endl;
		lua_pop(l, 1);//把栈顶的值移出栈，让key成为栈顶以便继续遍历  
	}
	lua_pop(l, 1);

	lua_close(l);
	system("pause");
    return 0;
}