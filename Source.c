#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char* value;
	struct node* next;
	struct node* prev;
} node;

typedef struct {
	node* head;
	int size;
} list;

node* swap(int swap_idx, list* l)							//cur key
{
	// Возвращает новый корень списка
	node* key = l->head, *cur;
	while (swap_idx != 1) {
		key = key->next; // дошли до сравниваемого элемента
		swap_idx--;
	}
	cur = key->prev;

	node* prev1, * prev2, * next1, * next2;
	prev1 = cur->prev;  // узел предшествующий cur
	prev2 = key->prev;  // узел предшествующий key
	next1 = cur->next; // узел следующий за cur
	next2 = key->next; // узел следующий за key
	if (key == next1)  // обмениваются соседние узлы
	{
		key->next = cur;
		key->prev = prev1;
		cur->next = next2;
		cur->prev = key;
		if (next2 != NULL)
			next2->prev = cur;
		if (cur != l->head)
			prev1->next = key;
	}
	if (cur == l->head)
		return(key);
	if (key == l->head)
		return(cur);
	return(l->head);
	
}

void swap_len(int* len1, int* len2) {
	int tmp = *len1;
	*len1 = *len2;
	*len2 = tmp;
}

void list_sorting(list* l,int* word_len) {
	int i, key;
	key = l->size;
	while(my_strcmp(key, l) < 0){
			l->head = swap(key, l);
			swap_len(&word_len[key - 1], &word_len[key - 2]);
			key--;
	}
}

 int my_strcmp(int idx, list* l) {
	if (idx == 1)
		return 1;
	node* key = l->head, * cur;
		while (idx != 1) {
		key = key->next; // дошли до сравниваемого элемента
		idx--;
	}
	cur = key->prev;
	char* val2 = key->value, * val1 = cur->value;
	while ((*val2 != 0) && (*val2 == *val1)) {
		val2++;
		val1++;
	}
	return *val2 - *val1;
}

void init(list* l) {
	l->head = NULL;
	l->size = 0;
}

void destroy(list* l) {
	node* cur = l->head;
	node* prev = NULL;
	while (cur != NULL) {
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}

void push_back(list* l, char* word, int* len) {
	node* n, * cur;
	n = (node*)malloc(sizeof(node));
	n->value = NULL;
	n->value = (char*)malloc(sizeof(char) * *len);
	for (int j = 0; j <= *len; j++) {
		n->value[j] = word[j];
	}
	n->next = NULL;
	if (l->head == NULL) {
		n->prev = NULL;
		l->head = n;
	}
	else {
		cur = l->head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = n;
		n->prev = cur;
	}
	l->size++;
}

void print(list* l) {
	int i = 0;
	node* cur = l->head;
	while (cur != NULL) {
		while (cur->value[i] != '\0') {
			printf("%c", cur->value[i]);
			i++;
		}
		cur = cur->next;
		printf("\n");
		i = 0;
	}
}

char* get_string(int* len, int* check) {
	*len = 0;
	int capacity = 1;

	if (*check == 0)
		while (getchar() != '\n');

	char* s = (char*)malloc(sizeof(char));

	char c = getchar();

	while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
		s[(*len)++] = c;

		if (*len >= capacity) {
			capacity *= 2;
			s = (char*)realloc(s, capacity * sizeof(char));
		}

		c = getchar();
		if (c == '\n')
			*check = 1;
		else
			*check = 0;
	}
	s[*len] = '\0';

	return s;
}


void Input_word(list* l, char* word, int* len, int* check, int* word_len) {
	printf("Enter word:\n");
	if (l->size >= 1 && *check == 1)
		*check = 0;
	word = get_string(len, check);
	if (word[0] == '\0') {
		printf("Incorrect input!\n");
		exit(1);
	}
	word_len[l->size] = *len;
	push_back(l, word, len);
	free(word);
}

void revers_list(list* l, list* rev_l, int* word_len) {
	int count = l->size;
	node* n, * cur, * cur_rev;
	cur = l->head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	while (count != 0) {
		n = (node*)malloc(sizeof(node));
		n->value = NULL;
		n->value = (char*)malloc(sizeof(char) * word_len[count - 1]);
		for (int j = 0; j <= word_len[count - 1]; j++) {
			n->value[j] = cur->value[j];
		}
		n->next = NULL;
		if (rev_l->head == NULL) {
			n->prev = NULL;
			rev_l->head = n;
		}
		else {
			if (count == l->size) {
				rev_l->head = n;
				n->prev = NULL;
			}
			else {
				cur_rev = rev_l->head;
				while (cur_rev->next != NULL)
					cur_rev = cur_rev->next;
				cur_rev->next = n;
				n->prev = cur_rev;
			}
		}
		rev_l->size++;
		count--;
		cur = cur->prev;
	}
}

int main() {
	int len, size = 0, capacity = 1;
	int check = 0, tmp = 0, choose = 0;
	list l, rev_l;
	init(&l);
	init(&rev_l);
	int* word_len = NULL;
	word_len = (int*)malloc(sizeof(int));
	char* word = NULL;
	while (!tmp) {
		printf("\n1.Input word to list\n2.Print list\n");
		printf("3.Printf reverse list\n4.Exit the programm");
			printf("\n\nSelect an action: ");
		if (scanf("%d", &choose) != 1 || choose < 1 || choose > 4) {
			printf("Incorrect input!");
			return 1;
		};
		switch (choose)
		{
		case 1:
			Input_word(&l, word, &len, &check, word_len);
			if (l.size == capacity) {
				capacity *= 2;
				word_len = (int*)realloc(word_len, capacity * sizeof(int));
			}
			if (check == 0)
				while (getchar() != '\n');
			list_sorting(&l, word_len);
			revers_list(&l, &rev_l, word_len);
			break;
		case 2:
			print(&l);
			break;
		case 3:
			print(&rev_l);
			break;
		case 4:
			free(word_len);
			destroy(&l); destroy(&rev_l);
			return 0;
		}
	}
}