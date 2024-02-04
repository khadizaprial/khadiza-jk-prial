
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

struct Product
{
    int productId;
    char name[20];
    float price;
    int quantity;
    struct Product *next;
};

struct Product * head=NULL;

void addProduct(int productId, char name[],float price,int quantity)
{
    struct Product *newProduct=(struct Product*)malloc(sizeof(struct Product));

    newProduct->productId=productId;
    strcpy(newProduct->name,name);
    newProduct->price=price;
    newProduct->quantity=quantity;
    newProduct->next=NULL;

    if (head==NULL)
    {
        head=newProduct;
         printf("Product added successfully.\n");

    }
   else
    {
        struct Product * temp=head;
        while (temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newProduct;
         printf("Product added successfully.\n");
    }
}


void displayProducts(struct Product *temp)
{
    if (temp==NULL)
    {
        printf("There is no product yet.\n");
        return;
    }
    else{

    printf("Products in the store: \n");
    struct Product *current=head;
    while (current !=NULL)
    {
        printf("Product ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n",current->productId,current->name,current->price,current->quantity);
        current=current->next;
    }
    }
}


void searchProduct(const char *searchName)
{
    if(head==NULL)
    {
        printf("No products here.\n");
        return;
    }

    struct Product *current=head;
    int found=0;

    printf("Search results for products with name '%s': \n",searchName);
    while(current !=NULL)
    {
        if(strcmp(current->name,searchName)==0)
        {
            printf("Product ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n",current->productId,current->name,current->price,current->quantity);
            found=1;
        }
        current=current->next;
    }

    if(!found)
    {
        printf("No products found with the name '%s'.\n",searchName);
    }
}


struct Product *searchProductById(int productId)
{
    struct Product *current=head;
    while(current !=NULL)
    {
        if(current->productId==productId)
        {
            return current;
        }
        current=current->next;
    }
    return NULL;
}


void updateProduct(int updateId)
{
    struct Product *current=head;
    while(current !=NULL)
    {
        if(current->productId==updateId)
        {
            printf("Enter updated information for Product ID: %d\n",updateId);
            printf("Enter Product Name: ");
            scanf("%s",current->name);
            printf("Enter Price: ");
            scanf("%f",&current->price);
            printf("Enter Quantity: ");
            scanf("%d",&current->quantity);
            printf("Product information updated successfully.\n");
            return;
        }
        current=current->next;
    }
    printf("Product with ID %d not found.\n",updateId);
}

void deleteProduct(int productId)
{
    struct Product *current=head;
    struct Product *prev = NULL;

    while (current !=NULL)
    {
        if (current->productId==productId)
        {
            if (prev==NULL)
            {
                head=current->next;
            }
        else
            {
                prev->next=current->next;
            }
            free(current);
            printf("Product with ID %d deleted successfully.\n", productId);
            return;
        }

        prev=current;
        current=current->next;
    }

    printf("Product with ID %d not found.\n",productId);
}

void freeList(struct Product *head)
{
    while (head !=NULL)
    {
        struct Product *temp=head;
        head=head->next;
        free(temp);
    }
}

int main()
{
    char userName[50];
    char userPassword[50];
    int loginAttempt = 0;

    // Admin login loop
    while (loginAttempt < 5)
    {
        printf("Admin user name: ");
        scanf("%s", userName);
        printf("Please enter your user password: ");
        scanf("%s", userPassword);

        if (strcmp(userName, "khadiza") == 0 && strcmp(userPassword, "12345") == 0)
        {
            printf("Welcome Admin!\n");
            break;
        }
        else
        {
            printf("Invalid login user name or password. Please try again.\n\n");
            loginAttempt++;
        }
    }

    int choice;

    do {
        printf("\nStore Management System\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product by Name\n");
        printf("4. Search Product by ID\n");
        printf("5. Update Product\n");
        printf("6. Delete Product\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                int productId, quantity;
                char name[SIZE];
                float price;

                printf("Enter Product ID: ");
                scanf("%d",&productId);
                printf("Enter Product Name: ");
                scanf("%s",name);
                printf("Enter Price: ");
                scanf("%f",&price);
                printf("Enter Quantity: ");
                scanf("%d",&quantity);

                addProduct(productId,name,price,quantity);
                break;
            }
            case 2:
                displayProducts(head);
                break;
            case 3:
            {
                char searchName[SIZE];
                printf("Enter Product Name to search: ");
                scanf("%s", searchName);
                searchProduct(searchName);
                break;
            }
            case 4:
            {
                int searchId;
                printf("Enter Product ID to search: ");
                scanf("%d",&searchId);
                struct Product *foundProduct=searchProductById(searchId);
                if (foundProduct !=NULL)
                {
                    printf("\nProduct found:\n");
                    printf("Product ID: %d\n", foundProduct->productId);
                    printf("Name: %s\n", foundProduct->name);
                    printf("Price: %.2f\n", foundProduct->price);
                    printf("Quantity: %d\n", foundProduct->quantity);
                }
                else
                {
                    printf("Product not found.\n");
                }
                break;
            }
            case 5:
            {
                int updateId;
                printf("Enter Product ID to update: ");
                scanf("%d",&updateId);
                updateProduct(updateId);
                break;
            }
            case 6:
            {
                int deleteId;
                printf("Enter Product ID to delete: ");
                scanf("%d",&deleteId);
                deleteProduct(deleteId);
                break;
            }
            case 7:
                printf("Closing the Store. Thank you");
                break;
            default:
                printf("Wrong Option Selected. Select the right option.\n");
        }
    }
    while (choice != 7);


    freeList(head);

    return 0;
}


