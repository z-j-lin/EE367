#include <stdio.h>
#include <stdlib.h>

struct Node {
	char data;
	struct Node *left;
	struct Node *right;
};

struct Node * createNode(char data);
struct Node * createTree(char encoding[], int *curr); 
void preorder(struct Node * root);
void inorder(struct Node * root);
void postorder(struct Node * root);
struct Node * delete(struct Node * root, char c);

void main(){
char tree[] = "hca//d/fe///mk//rn/p///";

int curr = 0;
struct Node * root = createTree(tree, &curr);
printf("Initial Tree Encoding: %s\n", tree);
printf("Preorder: ");
preorder(root);
printf("\n");
printf("Inorder: ");
inorder(root);
printf("\n");
printf("Postorder: ");
postorder(root);
printf("\n");

root = delete(root,'f'); 
root = delete(root,'c'); 
root = delete(root,'m'); 
printf("\nDeleted 'f', 'c', and then 'm'\n");
printf("Preorder: ");
preorder(root);
printf("\n");
printf("Inorder: ");
inorder(root);
printf("\n");
printf("Postorder: ");
postorder(root);
printf("\n");

return;
}

/* Deletes node 'c' from tree 'root' */
struct Node * delete(struct Node * root, char c)
{   
    //the base case where the root is empty
    if(root == NULL){
        return root;
    }
    
    //if c is larger than the current node char then target is on the right  
    if(c > root->data){
        root->right = delete(root->right, c);
    }
    //if the char is less than the one in the node then the target must be on the left
    else if(c < root->data){
        root->left = delete(root->left, c);
    }
    
    else{
        //when the node char is the same as c we delete the node 
        //can't simply just delete it though 
        //we have to check if the root that we are at has children
        //you can't kill someones parents without dealing with the children
        if(root->left == NULL){
            //if there are no left children
            //store right node in a temp node
            struct node *temp = root->right;
            //delete the current node 
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            // if there is a left node and no right node 
            //store the left node in a temporary node. 
            struct node *temp = root->left;
            //delete the root
            free(root);
            //return the temporary root linking the nodes in the left to the current node 
            return temp;
        }
        // for nodes with 2 children since node on the left is smaller
        //than the node on the right we move the right node value to the 
        //current node, keeping the rest in its place
        //make a copy of the left node
        struct node *temp = root->left
        //move the data from the left node to the root node 
        root->data = temp->data;
        //delete the node on the right since the value have been moved 
        //this will recursily move everything on the right of the deleting node up
        root->left = delete(root->left, temp->data);
    }
    //for recursive to work we need to return the root everytime  
    return root;
}

void preorder(struct Node * root)
{
if (root==NULL) return;
printf("%c", root->data);
preorder(root->left);
preorder(root->right);
}

void inorder(struct Node * root)
{
if (root==NULL) return;
inorder(root->left);
printf("%c", root->data);
inorder(root->right);
}

void postorder(struct Node * root)
{
if (root==NULL) return;
postorder(root->left);
postorder(root->right);
printf("%c", root->data);
}

struct Node * createNode(char data)
{
struct Node *p = (struct Node *) malloc(sizeof(struct Node));
p->left = NULL;
p->right = NULL;
p->data = data;
}

struct Node * createTree(char encoding[], int *curr) 
{
if (encoding[*curr] == '/') { 
	return NULL;
}
struct Node *p = createNode(encoding[*curr]);
(*curr)++;
p->left = createTree(encoding, curr);
(*curr)++;
p->right = createTree(encoding, curr);

return p;
}


