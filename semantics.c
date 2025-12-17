#include <stdio.h>
#include <stdlib.h>
#include "semantics.h"
#include "symtab.h"

/* Kiểm tra tên định danh chưa được khai báo trong scope hiện tại */
void checkFreshIdent(char *name) {
  Object *obj = findObject(symtab.currentScope->objList, name);
  if (obj != NULL) {
    printf("Semantic error: identifier '%s' already declared\n", name);
    exit(1);
  }
}

/* Kiểm tra định danh đã được khai báo (tìm từ scope hiện tại ra ngoài) */
Object* checkDeclaredIdent(char *name) {
  Scope *scope = symtab.currentScope;
  Object *obj = NULL;

  while (scope != NULL) {
    obj = findObject(scope->objList, name);
    if (obj != NULL)
      return obj;
    scope = scope->outer;
  }

  printf("Semantic error: identifier '%s' not declared\n", name);
  exit(1);
}

/* Kiểm tra hằng */
Object* checkDeclaredConstant(char *name) {
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_CONSTANT) {
    printf("Semantic error: '%s' is not a constant\n", name);
    exit(1);
  }
  return obj;
}

/* Kiểm tra kiểu */
Object* checkDeclaredType(char *name) {
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_TYPE) {
    printf("Semantic error: '%s' is not a type\n", name);
    exit(1);
  }
  return obj;
}

/* Kiểm tra biến */
Object* checkDeclaredVariable(char *name) {
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_VARIABLE && obj->kind != OBJ_PARAMETER) {
    printf("Semantic error: '%s' is not a variable\n", name);
    exit(1);
  }
  return obj;
}

/* Kiểm tra hàm */
Object* checkDeclaredFunction(char *name) {
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_FUNCTION) {
    printf("Semantic error: '%s' is not a function\n", name);
    exit(1);
  }
  return obj;
}

/* Kiểm tra thủ tục */
Object* checkDeclaredProcedure(char *name) {
  Object *obj = checkDeclaredIdent(name);
  if (obj->kind != OBJ_PROCEDURE) {
    printf("Semantic error: '%s' is not a procedure\n", name);
    exit(1);
  }
  return obj;
}

/* Kiểm tra L-value (biến hoặc tham chiếu) */
Object* checkDeclaredLValueIdent(char *name) {
  Object *obj = checkDeclaredIdent(name);

  if (obj->kind == OBJ_VARIABLE)
    return obj;

  if (obj->kind == OBJ_PARAMETER &&
      obj->paramAttrs->kind == PARAM_REFERENCE)
    return obj;

  printf("Semantic error: '%s' is not a valid l-value\n", name);
  exit(1);
}
