#include<iostream>
using namespace std ;
class Node 
{
	public :
	int data ;	
	int height ;
	Node *left ;
	Node *right ;	
	Node(int val )
	{
		data =  val ;
		height = 0 ;
		left = right = NULL ;
	}
};

class AVL_Tree
{
	Node *Root ;
	public :
		AVL_Tree() {Root = NULL ;}
		void AVL_Insert(int data) ;
		void Insert(Node **root , int val);  // 1
		bool Search(int key) ;			//2
		void Delete(int val) ;
		void Del(Node **root , int key) ;	//3
		void sucessor(Node *roo1 ,Node *root2) ;	//4
		void DeleteTree() ;			
		void DelTree(Node *root) ;			//5
		void right_rotate(Node **root) ;		//6
		void left_rotate(Node **root);			//7
		int height(Node *root) ;			//8
		int max(int left , int right) ;			//9
		int abs(int a ) { return a >= 0 ?a:-a ;}	//10
		bool AVL_checker() ;				//11
		bool AVL_balance(Node *root);
		void display();
		void preorder(Node *root) ;			//12
		bool isEmpty(){  return Root == NULL ? true :  false ;} //13
};

void  AVL_Tree:: Delete(int key)
{
	Del(&Root , key) ;
}

void AVL_Tree::Del(Node **root , int key)
{
	if(*root == NULL)
	{	cout << "Element found " ;
		return  ;
	}
	
	if((*root)->data == key)
	{
		if((*root)->left == NULL)
		{
			Node *temp =  (*root)->right ;
			delete *root ;
			*root =  temp ;
			return ;
		}
		else if((*root)->right  == NULL)
		{
			Node *temp = (*root)->left ;
			delete *root ;
			*root = temp ;
			return ;
		}
		else
		{
			sucessor(*root , (*root)->right) ;
		        Del(&(*root)->right, key) ;
		}
	}
	else if((*root)->data  > key )
	{
		  Del(&(*root)->left , key ) ;
	}
	else
	{  // only for the visibilty { }
		 Del(&(*root)->right , key) ;   // i think that (*root)-.le   = use less 
	}
	
	if(abs(height((*root)->left) - height((*root)->right) ) <= 1)
		{
			(*root)->height = max(height((*root)->left) , height((*root)->right)) + 1 ;
		}
	else if(height((*root)->left) - height((*root)->right)  > 1)
	{
		if(height((*root)->left->right) > height((*root)->left->left))
			{
				left_rotate(&(*root)->left) ;
			}
		right_rotate(root ) ;
	}
	else
	{
		if(height((*root)->right->left) > height((*root)->right->right))
		{
			right_rotate(&(*root)->right) ;
		}
		
		left_rotate(root) ;
	}
}
void AVL_Tree:: sucessor(Node *root1 , Node *root2)
{

	if(root2->left == NULL)
	{
		root1->data = root2->data ^ root1->data ;
		root2->data = root2->data ^ root1->data ;
		root1->data = root2->data ^ root1->data ;
		return;
	}
	sucessor(root1 , root2->left) ;
}

void AVL_Tree :: display()
{
	preorder(Root);
}

void AVL_Tree::preorder(Node *root)
{
	if(root)
	{
		
		preorder(root->left) ;
		cout << root->data <<  "    " ;
		preorder(root->right) ;
	}
}
bool AVL_Tree::AVL_checker()
{
  return AVL_balance(Root) ;
}

bool AVL_Tree::AVL_balance(Node *root)
{
	if(root)
	{
		int left  = AVL_balance(root->left);
		int right = AVL_balance(root->right);	
		if(left == false || right == false)
			return false ;
		if(abs( height(root->left) - height(root->right) ) <= 1)
			return true ;
		else 
			return false ;
	}				
	return true ;
}
bool AVL_Tree::Search(int key)
{
	Node *temp = Root ;
	
	while(temp && temp->data != key)
		{
			if(temp->data > key )
				temp = temp->left ;
			else
				temp = temp -> right ;
		}
	if(temp)
		return true ;
		
	return false ;
}
void AVL_Tree::DeleteTree()
{
	DelTree(Root) ;
}

void AVL_Tree::DelTree(Node * root)
{
	if(root)
	{
		DelTree(root->left);
 		DelTree(root->right);
		delete root ;
	}
}

/// let assume that every value is distinct
void AVL_Tree::Insert(Node **root ,int val)
{

	if(*root == NULL)
	{
		*root = new Node(val) ;
		return ;
	}	
	
	if((*root)->data > val)
		Insert(&(*root)->left , val );
	else 
		Insert(&(*root)->right , val) ;

	if(abs(height((*root)->left ) - height((*root)->right)) <= 1)
			(*root)->height  = max(height((*root)->left) , height((*root)->right)) + 1 ;
	else if(height((*root)->left) - height((*root)->right) > 1)  // this indicate that left sub tree is heavy
	{
		if(height((*root)->left->right) > height((*root)->left->left) )
			left_rotate(&(*root)->left );
		
		right_rotate(root) ;
	}
	else   /// this indicates that the right sub tree is heavy
	{
		if( height( (*root)->right->left )  >  height( (*root)->right->right ))
			right_rotate(&(*root)->right) ;
		left_rotate(root) ;
	}
}
void AVL_Tree::AVL_Insert(int val)
{
	Insert(&Root , val );
}
int AVL_Tree::max(int left , int right)
{
	return left > right ? left : right ;
}

int AVL_Tree::height(Node *root)
{
	if(!root)
		return -1 ;
	return root->height ;
}
			
void AVL_Tree::left_rotate(Node **root) 
{
	Node *temp = (*root)->right  ;
	Node *R = *root ;
	
	R->right = temp->left ;
	temp->left = R ;
	// balancing the height 
//	Here R and  the temp nod is the affected node 
	// and also the R should be the managed first    then we will manage the   height of the temp   ---->reason is clear
	R->height = max(height(R->left) , height(R->right) ) + 1 ;
	temp->height = max(height(temp->left) ,height( temp->right)) +1 ;

	*root = temp ;
}

void AVL_Tree :: right_rotate(Node **root)
{
	Node *temp = (*root)->left ;
	Node *R = *root ;
	
	R->left = temp->right ;
	temp->right = R ;
 	// balancing the height 
	
	R->height    = 	max(height(R->left) , height(R->right) ) + 1 ;
	temp->height = max(height(temp->left) ,height( temp->right)) + 1 ;
	*root = temp ;
}

int main()
{
	int data[] = {23,3243,345,567,78,9,234,342,121,89,141,57,10,179,589} ;
	AVL_Tree obj ;
	for(int i =  0 ; i <15 ; i++)
		obj.AVL_Insert(data[i]);
 	
	obj.display() ;
	cout << obj.AVL_checker() ;
	cout<<"\n\n";
	for(int i =  0 ; i <15 ; i++)
	{
		obj.Delete(data[i]);
		cout << "\n\n"<< obj.AVL_checker()<< endl ;
		obj.display() ;
	}
	cout<< "checking that tree is empty or not(reason is the dangling pointer   , if 0 then not good for the big manipulation ) : " <<obj.isEmpty() << endl;	
	obj.DeleteTree() ;
}
