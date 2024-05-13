// USING A STACK FOR ARITHMETIC
/*
infix notation: a+b*c+(d*e+f)*g
postfix notation: abc*+de*f+g*+
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_POS -1
#define MIN_STACK_SIZE 5

struct ElementType {
	char value;
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
struct ElementType pop(Stack s) {
    if (is_empty(s)) {
        printf("The stack is currently empty. You cannot pop an empty stack!!!\n");
        // Trong trường hợp stack rỗng, bạn có thể trả về một giá trị không hợp lệ hoặc báo lỗi khác
        return (struct ElementType){0}; // Ví dụ trả về giá trị mặc định
    } else {
        s->tos--; // Giảm chỉ số của đỉnh stack
        return s->stack_array[s->tos + 1]; // Trả về phần tử đã bị pop
    }
}

// truy xuất giá trị của phần tử trên cùng
struct ElementType top(Stack s) {
	if (is_empty(s)) 
		printf("The stack is currently empty. You cannot top an empty stack!!!\n");
	else 
		return s->stack_array[s->tos];
} 

// kiểm tra xem phần tử có phải là toán hạng không
int isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Kiểm tra sự ưu tiên của các toán tử
int prec(char ch)
{
	if (ch == '+' || ch == '-') return 1;
	if (ch == '*' || ch == '/') return 2;
	return 0;
}
void infixToPostfix(char *infix)
{
	char postfix[100];
	int lengthPostfix = 0;
	Stack Operator = create_stack(100);
	
	// bo qua khoang trang va dau tab trong bieu thuc
	while (*infix != '\0' && (*infix == ' ' || *infix == '\t')) {
        infix++;
    }

	while(*infix != '\0') {
		char c = *infix;

		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
			postfix[lengthPostfix++] = c;
		}
		else if (c == '(') {
			push(Operator, (struct ElementType) {c});
		}
		else if (c == ')') {
			// Lấy các toán tử từ stack đưa vào biểu thức hậu tố cho đến khi gặp '('
			while(!is_empty(Operator) && top(Operator).value != '(') {
				postfix[lengthPostfix++] = pop(Operator).value;
			}
			// Loại bỏ dấu '(' khỏi stack
			if (!is_empty(Operator) && top(Operator).value == '(') {
			    pop(Operator);
			}
		}
		else if (isOperator(c)) {
			// Xử lý toán tử
				while (!is_empty(Operator) && prec(c) <= prec(top(Operator).value)) {
					postfix[lengthPostfix++] = pop(Operator).value; 
				}
				// Đẩy toán tử hiện tại vào stack
				push(Operator, (struct ElementType) {c});
			}
			infix++; // Di chuyển đến kí tự tiếp theo trong biểu thức
		}

		// Lấy các toán tử còn lại từ stack đưa vào biểu thức hậu tố
		while(!is_empty(Operator)) {
			postfix[lengthPostfix++] = pop(Operator).value;
		}

		printf("Postfix is: %s\n", postfix);	
}
int main(){
	char infixExpression[] = "a+b*c+(d*e+f)*g";

	infixToPostfix(infixExpression);
	return 0;
}