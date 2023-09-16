#include <stdio.h>
#include<stdlib.h>
#include<string.h> 
struct ShoppingItem
{
    char name[50]; // ��Ʒ����
    int quantity; // ��Ʒ����
    struct ShoppingItem* next; // ָ����һ���ڵ��ָ��
};
struct ShoppingItem* shoppingList = NULL;
struct ShoppingItem* addItem()
{
	char itemName[50];
	int itemQuantity;
	struct ShoppingItem* shoppinglist=NULL;
    while(1)
    {
        struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
        scanf("%s%d",newItem->name,&newItem->quantity);
    	newItem->next=NULL;
        if(newItem->name[0] == '0'){
            break;
        }
    	if(shoppinglist==NULL)
    	{
    		shoppinglist=newItem;
		}
		else
		{
			newItem->next = shoppinglist;
        	shoppinglist = newItem;
		}

	}
    return shoppinglist;
}
void removeItem(char itemName[])
{
	
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* previous = NULL;
    while(current != NULL)
	{
        if (strcmp(current->name, itemName) == 0)
		{
            if (previous != NULL)
			{
            	previous->next = current->next;
            }
			else
			{
            	shoppingList = current->next;
            }
            free(current);
            break;
        }
        previous=current;
        current=current->next;
    }
    return ;
}

void displayList()
{
    struct ShoppingItem* current = shoppingList;
    printf("�����嵥:\n");
    while (current != NULL)
	{
        printf("%s - ������%d\n", current->name, current->quantity);
        current=current->next;
    }
}

void updateQuantity(char itemName[], int newItemQuantity)
{
    struct ShoppingItem* current = shoppingList;
    while(current != NULL)
	{
        if (strcmp(current->name, itemName) == 0)
		{
            current->quantity=newItemQuantity;
            break;
        }
        current = current->next;
    }
}

void clearList()
{
    struct ShoppingItem* temp = NULL;
    while (shoppingList != NULL)
	{
        temp=shoppingList;
        shoppingList=shoppingList->next;
        free(temp);
    }
    return ;
}

int totalQuantity()
{
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while(current != NULL)
	{
        total=total+current->quantity;
        current = current->next;
    }
    return total;
}

void findItem(char itemName[])
{
    struct ShoppingItem* current = shoppingList;
    printf("������Ʒ \"%s\" :\n", itemName);
    while (current != NULL) 
	{
        if (strcmp(current->name, itemName) == 0)
		{
        	printf("%s - ������%d\n", current->name, current->quantity);
        	return;
    	}
        current=current->next;
    }
    printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
}

void sortList()
{
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;
    while (current != NULL)
	{
        nextItem = current->next;
        while (nextItem != NULL)
		{
            if (strcmp(current->name, nextItem->name) > 0)
			{
                strcpy(tempName,current->name);
                strcpy(current->name,nextItem->name);
                strcpy(nextItem->name,tempName);
                tempQuantity = current->quantity;
                current->quantity = nextItem->quantity;
                nextItem->quantity = tempQuantity;
            }
            nextItem = nextItem->next;
        }
        current = current->next;
    }
}

void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2)
{
    struct ShoppingItem* current = *list1;
    
    // ��������һ�������嵥��ĩβ
    while(current->next!=NULL)
	{
        current=current->next;
    }
    current->next = *list2;
    *list2 = NULL; // ��յڶ��������嵥��ͷָ�룬��ֹ����
}

void deleteItem(char itemName[], int deleteAll)
{
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL)
	{
        if (strcmp(current->name, itemName) == 0)
		{
            if (prev == NULL)
			{
                // ���Ҫɾ�����ǵ�һ���ڵ�
                struct ShoppingItem* temp = shoppingList;
                shoppingList=shoppingList->next;
                free(temp);
                if (!deleteAll) break;
            }
			else
			{
                // ���Ҫɾ���Ĳ��ǵ�һ���ڵ�
                prev->next=current->next;
                free(current);
                current = prev->next;
                if (!deleteAll) break;
            }
        }
		else 
		{
        prev = current;
        current = current->next;
        }
    }
}

int main()
{
    int num=0,quantity=0;
    char name[50];
    do
    {
    	printf("�������������ִ��ţ�");
    	scanf("%d",&num); 
    	switch(num)
    	{
    		case 1:
    		{
    			shoppingList=addItem();
    			displayList();
    			continue;
			}
			case 2:
			{
				printf("������Ҫ�Ƴ�����Ʒ��\n");
				scanf("%s",name);
				removeItem(name);
				displayList();
				continue;
			}
			case 3:
			{
				displayList();
				continue;
			}
			case 4:
			{
				printf("��������Ʒ�����޸ĵ�����: \n");
            	scanf("%s%*c%d",name, &quantity);
            	updateQuantity(name, quantity);
            	printf("�޸���ɣ��嵥���£�\n");
            	displayList();
            	printf("\n");
            	continue;
			}
			case 5:
			{
				clearList();
				continue;
			}
			case 6:
			{
				printf("��ǰ��Ʒ������Ϊ��%d\n",totalQuantity());
				continue;
			}
			case 7:
			{
				printf("������Ҫ���ҵ���Ʒ��\n");
            	scanf("%s",name);
            	findItem(name);
            	continue;
			}
			case 8:
			{
				sortList();
            	printf("������ɣ��嵥���£�\n");
            	displayList();
            	printf("\n");
            	continue;
			}
			case 9:
			{
				struct ShoppingItem* list1 = NULL;
            	struct ShoppingItem* list2 = NULL;
            	printf("�嵥1\n");
            	printf("�������嵥1����Ʒ���Ƽ�����: \n");
                list1 = addItem();
            	printf("�嵥2\n");
            	printf("�������嵥2����Ʒ���Ƽ�����: \n");
                list2 = addItem();
            	clearList();
            	mergeLists(&list1, &list2);
            	shoppingList = list1;
            	printf("�ϲ���ɣ��嵥���£�\n");
            	displayList();
            	printf("\n");
            	continue;
			}
			case 10:
			{
				printf("������Ҫɾ������Ʒ��\n");
            	int f;
            	scanf("%s",name);
            	printf("�Ƿ�ȫ��ɾ������Ϊ[1]������Ϊ[0]\n");
            	scanf("%d",&f);
            	deleteItem(name, f);
            	printf("ɾ���ɹ����嵥���£�\n");
            	displayList();
            	printf("\n");
            	continue;
			}
		}
		num=0;
		quantity=0;
	}while(num>=1&&num<=10);
	return 0;
}

 
