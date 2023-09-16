#include <stdio.h>
#include<stdlib.h>
#include<string.h> 
struct ShoppingItem
{
    char name[50]; // 商品名称
    int quantity; // 商品数量
    struct ShoppingItem* next; // 指向下一个节点的指针
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
    printf("购物清单:\n");
    while (current != NULL)
	{
        printf("%s - 数量：%d\n", current->name, current->quantity);
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
    printf("查找商品 \"%s\" :\n", itemName);
    while (current != NULL) 
	{
        if (strcmp(current->name, itemName) == 0)
		{
        	printf("%s - 数量：%d\n", current->name, current->quantity);
        	return;
    	}
        current=current->next;
    }
    printf("未找到商品 \"%s\"。\n", itemName);
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
    
    // 遍历到第一个购物清单的末尾
    while(current->next!=NULL)
	{
        current=current->next;
    }
    current->next = *list2;
    *list2 = NULL; // 清空第二个购物清单的头指针，防止误用
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
                // 如果要删除的是第一个节点
                struct ShoppingItem* temp = shoppingList;
                shoppingList=shoppingList->next;
                free(temp);
                if (!deleteAll) break;
            }
			else
			{
                // 如果要删除的不是第一个节点
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
    	printf("请输入任意数字代号：");
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
				printf("请输入要移除的商品：\n");
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
				printf("请输入商品名和修改的数量: \n");
            	scanf("%s%*c%d",name, &quantity);
            	updateQuantity(name, quantity);
            	printf("修改完成，清单如下：\n");
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
				printf("当前商品总数量为：%d\n",totalQuantity());
				continue;
			}
			case 7:
			{
				printf("请输入要查找的商品：\n");
            	scanf("%s",name);
            	findItem(name);
            	continue;
			}
			case 8:
			{
				sortList();
            	printf("排序完成，清单如下：\n");
            	displayList();
            	printf("\n");
            	continue;
			}
			case 9:
			{
				struct ShoppingItem* list1 = NULL;
            	struct ShoppingItem* list2 = NULL;
            	printf("清单1\n");
            	printf("请输入清单1的商品名称及数量: \n");
                list1 = addItem();
            	printf("清单2\n");
            	printf("请输入清单2的商品名称及数量: \n");
                list2 = addItem();
            	clearList();
            	mergeLists(&list1, &list2);
            	shoppingList = list1;
            	printf("合并完成，清单如下：\n");
            	displayList();
            	printf("\n");
            	continue;
			}
			case 10:
			{
				printf("请输入要删除的商品：\n");
            	int f;
            	scanf("%s",name);
            	printf("是否全部删除？是为[1]，不是为[0]\n");
            	scanf("%d",&f);
            	deleteItem(name, f);
            	printf("删除成功，清单如下：\n");
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

 
