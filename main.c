#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <stdlib.h>

#define MACHINE_STACK_CAPACITY 1024
typedef int64_t Word;
// int main(int argc, char *argv[]) {
typedef struct {
  Word stack[MACHINE_STACK_CAPACITY];
  size_t stack_size;

} Machine;
typedef enum {
  INST_PUSH,
  INST_PLUS,
} Inst_Type;

typedef enum {
  TRAP_OK,
  TRAP_STACK_OVERFLOW,
  TRAP_STACK_UNDERFLOW,
  TRAP_ILLEGAL_INST
} Trap;
typedef struct {
  Inst_Type type;
  Word operand;

} Inst;

Inst instruction_push(Word word) {

  return (Inst){
      .type = INST_PUSH,
      .operand = word,
  };
}

Inst instruction_plus(void) { return (Inst){.type = INST_PLUS}; }
Trap machine_execute_inst(Machine *machine, Inst inst) {
  switch (inst.type) {
  case INST_PUSH:
    if (machine->stack_size >= MACHINE_STACK_CAPACITY) {
      return TRAP_STACK_OVERFLOW;
    };
    machine->stack[machine->stack_size++] = inst.operand;
    break;
  case INST_PLUS:
    if (machine->stack_size < 2) {
      return TRAP_STACK_UNDERFLOW;
    }
    machine->stack[machine->stack_size - 2] +=
        machine->stack[machine->stack_size - 1];
    machine->stack_size -= 1;
    break;

  default:
    return TRAP_ILLEGAL_INST;
  }
  return TRAP_OK;
}

void exec_dump(const Machine *machine) {
  printf("Stack : \n");

  if (machine->stack_size > 0) {
    for (size_t i = 0; i < machine->stack_size; ++i) {
      printf("   %ld\n", machine->stack[i]);
    }
  } else {
    printf("[empty] \n");
  }
}

Machine machine = {0};

int main() {
  exec_dump(&machine);

  machine_execute_inst(&machine, instruction_push(78));
  exec_dump(&machine);

  // printf("hello, world \n");
  return 0;
}
