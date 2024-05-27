#include <stdio.h>
#include <stdlib.h>

#define EMPTY_POS -1
#define MIN_STACK_SIZE 5

struct ElementType {
	int value;
};

struct StackRecord {
	unsigned int stack_size;
	int tos;
	struct ElementType *stack_array;
};

typedef struct StackRecord *Stack;

// hàm kiểm tra xem stack có rỗng không
int is_empty(Stack s) {
	return s->tos == EMPTY_POS;
}

// hàm làm rỗng ngăn xếp
void make_empty(Stack s) {
	s->tos = EMPTY_POS;
}

// hàm giải phóng dữ liệu
void dispose(Stack s) {
	if (s!=NULL) {
		free(s->stack_array);
		free(s);
	} 
}

// tạo một stack mới
Stack create_stack(unsigned int max_elements){
	if (max_elements < MIN_STACK_SIZE){
		printf("Stack size is too small!!!\n");
		return NULL;
	}
	
	Stack s = malloc(sizeof(struct StackRecord));
	s->stack_array = malloc(sizeof(struct ElementType)*max_elements);
	
	s->stack_size = max_elements;
	s->tos = EMPTY_POS;
	return s;
}

// kiếm tra xem stack có full không
int is_full(Stack s) {
	return s->tos == (s->stack_size - 1);
}

// thêm phần tử vào stack 
void push(Stack s, struct ElementType e) {
	if (is_full(s)) 
		printf("The stack is full already!!!\n");
	else 
		s->stack_array[++s->tos] = e;	
}

// pop phần tử ra khỏi stack
void pop(Stack s) {
	if (is_empty(s)) 
		printf("The stack is currently empty. You cannot pop an empty stack!!!\n");
	else 
		s->stack_array[s->tos--];
}

// truy xuất giá trị của phần tử trên cùng
struct ElementType top(Stack s) {
	if (is_empty(s)) 
		printf("The stack is currently empty. You cannot top an empty stack!!!\n");
	else 
		return s->stack_array[s->tos];
} 

// hiển thị các giá trị của các phần tử có trong stack
void show_stack(Stack s){
	if (is_empty(s)) {
		printf("The stack is empty!!!\n");
		return;
	}		
	printf("Current state of the stack is: ");
	for (int i = s->tos; i>=0;i--) {
		printf("%d ",s->stack_array[i].value);
	}
	printf("\n");
}

int main(){
	struct ElementType e1,e2,e3,e4,e5,e;
	e1.value = 4; e2.value=5; e3.value=-8; e4.value=10; e5.value=19;
	Stack s = create_stack(100);
	push(s,e1); push(s,e2); push(s,e3); push(s,e4); push(s,e5); 
	show_stack(s);

	e = top(s);
	printf("Value of the top item is: %d\n",e.value);

	// struct ElementType a = pop(s);
	pop(s);
	show_stack(s);

	dispose(s);
	return 0;
}