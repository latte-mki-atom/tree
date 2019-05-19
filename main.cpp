#include <iostream>

using namespace std;

struct tree_elem
{
	int key;
	unsigned char height;
	tree_elem* left;
	tree_elem* right;
	tree_elem(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(tree_elem* gh)
{
	return gh?gh->height:0;
}

int bfactor(tree_elem* gh)
{
	return height(gh->right)-height(gh->left);
}

void heightfix(tree_elem* gh)
{
	unsigned char ugh = height(gh->left);
	unsigned char agh = height(gh->right);
	gh->height = (ugh>agh?ugh:agh)+1;
}

tree_elem* rightrotation(tree_elem* gh)
{
	tree_elem* th = gh->left;
	gh->left = th->right;
	th->right = gh;
	heightfix(gh);
	heightfix(th);
	return th;
}

tree_elem* rotateleft(tree_elem* th)
{
	tree_elem* gh = th->right;
	th->right = gh->left;
	gh->left = th;
	heightfix(th);
	heightfix(gh);
	return gh;
}

tree_elem* balance(tree_elem* gh)
{
	heightfix(gh);
	if( bfactor(gh)==2 )
	{
		if( bfactor(gh->right) < 0 )
			gh->right = rightrotation(gh->right);
		return rotateleft(gh);
	}
	if( bfactor(gh)==-2 )
	{
		if( bfactor(gh->left) > 0  )
			gh->left = rotateleft(gh->left);
		return rightrotation(gh);
	}
	return gh;
}

tree_elem* insert(tree_elem* gh, int k)
{
	if( !gh ) return new tree_elem(k);
	if( k<gh->key )
		gh->left = insert(gh->left,k);
	else
		gh->right = insert(gh->right,k);
	return balance(gh);
}

tree_elem* searchmin(tree_elem* gh)
{
	return gh->left?searchmin(gh->left):gh;
}

tree_elem* deletemin(tree_elem* gh)
{
	if( gh->left==0 )
		return gh->right;
	gh->left = deletemin(gh->left);
	return balance(gh);
}

tree_elem* remove(tree_elem* gh, int k)
{
	if( !gh ) return 0;
	if( k < gh->key )
		gh->left = remove(gh->left,k);
	else if( k > gh->key )
		gh->right = remove(gh->right,k);
	else //  k == gh->key
	{
		tree_elem* th = gh->left;
		tree_elem* r = gh->right;
		delete gh;
		if( !r ) return th;
		tree_elem* min = searchmin(r);
		min->right = deletemin(r);
		min->left = th;
		return balance(min);
	}
	return balance(gh);
}
