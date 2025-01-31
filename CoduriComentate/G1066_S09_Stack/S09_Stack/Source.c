
///// DONE ///// STACK  -  POP = scoate din stack / PUSH = adauga in stack / PEEK = din 1->2->3->4->5->NULL, dupa peek(&stack) , stack ul va deveni 2->NULL.

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <string.h>
#include "memory.h"
#include <stdbool.h>
//keyboad - stdin
//console - stdout
#define LINE_BUFFER 128

typedef struct Employee {
	short code;
	char* name;
	char* department;
	double salary;
}Employee;

//typedef struct Employee Employee;
typedef struct Node
{
	Employee* info;
	struct Node* pNext;
}Node;

typedef struct Node Stack;

/*functions' signatures for memory management*/
Employee* createInfo(short, char*, char*, double);
Node* createNode(Employee*);

/*functions' signatures for list operations*/
void printList(Node*);
void printInfo(Employee*);
void push(Node**, Employee*);
Employee* pop(Node**);
Employee* peek(Node*);
bool isEmpty(Node*);

void main()
{
	Node* list = NULL;
	Stack* stack = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	char lineBuffer[LINE_BUFFER], * token, sep_list[] = ",\n"; // virgula si sfarsitul de linie separa cuvintele intre ele
	Employee* emp = NULL;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			emp = (Employee*)malloc(sizeof(Employee)); // creez un obiect de tip employee

			//adaug la employee codul citit
			token = strtok(lineBuffer, sep_list);
			emp->code = atoi(token);

			//adaug la employee numele citit
			token = strtok(NULL, sep_list);
			emp->name = (char*)malloc(strlen(token) + 1);
			strcpy(emp->name, token);

			//adaug la employee departamentul citit
			token = strtok(NULL, sep_list);
			emp->department = (char*)malloc(strlen(token) + 1);
			strcpy(emp->department, token);

			//adaug la employee salariul citit
			token = strtok(NULL, sep_list);
			emp->salary = atof(token);

			//adaug employee ul in stack
			push(&stack, emp);
		}

		printf("\n-------------- Print Stack -----------\n");
		printList(stack);
		printf("\n---------------------------------\n");
		//Employee* emp = peek(stack);
		printf("\n\n\n\n");
		Employee* emp = pop(&stack); // scot cel mai recent nod din stack. Retin ce am scos cat sa afisez.
		printf("Scos din Stack: %s\n",emp->name);
		printf("\n");
		printf("\n-------------- Print Stack -----------\n");
		printList(stack);

		stack = peek(stack); // dau override la stack sa aiba un singur element. (cel care era pe pozitia 2)
		printf("\n\n\n\n");
		printf("\n-------------- Print Primu elem din Stack -----------\n");
		printList(stack);

		//stack = peek(stack);
		printf("\n\n\n\n");

		if (isEmpty(stack) == true) {
			printf("Stack is empty");
		}
		else {
			printf("Stack have nodes in it.");
		}
		//printf(isEmpty(stack));


		//while ((emp = pop(&stack)) != NULL)
		//{
		//	printInfo(emp);
		//}

	}
}

Employee* peek(Stack* topStack) // primul element din stack (cel mai recent) ia valoarea celui de pe locul 2 si face lista sa il contina doar pe el. Adica: 1->2->3->4->5->6->null va deveni dupa peek: 2->null.
{
	if (topStack->pNext != NULL) {
		topStack = topStack->pNext;
		topStack->pNext = NULL;
	}
	else {
		topStack = NULL;
	}
	return topStack;
}

void push(Stack** topStack, Employee* emp) // adaugi un element la sfarsitul stackului.
{
	Node* node = createNode(emp);
	node->pNext = *topStack;
	*topStack = node;
}

bool isEmpty(Stack* topStack)
{
	if (topStack == NULL)
		return true;
	else
		return false;
}

Employee* pop(Stack** topStack) // stergi ultimul element adaugat in stack (primul de deasupra) si il returnezi daca vrei sa afisezi ce ai sters, daca nu.. fa functia void
{
	Employee* value = NULL;
	if (!isEmpty(*topStack))
	{
		value = (*topStack)->info;
		Node* tmp = *topStack;
		*topStack = tmp->pNext;
		free(tmp);
	}
	return value;
}

void printInfo(Employee* emp)
{
	printf("Code: %d - Name: %s - Dept: %s - Salary: %f\n",
		emp->code,
		emp->name,
		emp->department,
		emp->salary);
}
void printList(const Node* head)
{
	while (head)
	{
		printInfo(head->info);
		head = head->pNext;
	}
}
Employee* createInfo(short code, char* name, char* dept, double salary) // creezi un obiect de tip employee
{
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->department = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->department, dept);
	emp->salary = salary;
	return emp;
}

Node* createNode(Employee* emp) // creezi un nod si adaugi obiectul creat anterior.
{
	//declare and allocate memory
	Node* node = (Node*)malloc(sizeof(Node));
	//initialize variable
	node->info = emp;
	node->pNext = NULL;
	//return value
	return node;
}