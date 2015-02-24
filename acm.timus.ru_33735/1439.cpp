#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class TKey>
struct TreapNode
{
	TreapNode* Left;
	TreapNode* Right;

	int Priority, DescendantCount;
	TKey Key;
	
	TreapNode(TKey key, int priority = rand()%RAND_MAX) : Key(key), Priority(priority)
	{
		Left = Right = NULL;
		DescendantCount = 1;
	}

	void RefreshDescendants()
	{
		DescendantCount = 1 + GetDescendantCount(Left) + GetDescendantCount(Right);
	}

	static int GetDescendantCount(TreapNode<TKey>* node)
	{
		if(node != NULL)
			return node->DescendantCount;
		return 0;
	}
};

template<class TItem>
struct TreapSet
{
	typedef TreapNode<TItem> Node;
	
	Node* tree;

	TreapSet() : tree(NULL)
	{ }
	
	/*static Node* Join(Node* less, Node* greater)
	{
		if(less == NULL)
			return greater;
		if(greater == NULL)
			return less;
		
		if(less->Priority > greater->Priority)
		{
			less->Right = Join(less->Right, greater);
			less->RefreshDescendants();
			return less;
		}
		else
		{
			greater->Left = Join(less, greater->Left);
			greater->RefreshDescendants();
			return greater;
		}
	}*/

	static void Split(Node* root, Node*& less, Node*& greater, TItem key)
	{
		if(root == NULL)
			return;

		if(root->Key < key)
		{
			less = root;
			Node* old = root->Right;
			root->Right = NULL;
			Split(old, root->Right, greater, key);
		}
		else if(root->Key > key)
		{
			greater = root;
			Node* old = root->Left;
			root->Left = NULL;
			Split(old, less, root->Left, key);
		}
		else
		{
			less = root->Left;
			greater = root->Right;
		}

		root->RefreshDescendants();
	}
	
	void Insert(Node*& dest, Node node)
	{
		if(dest == NULL)
		{
			dest = new Node(node);
			return;
		}
		
		if(dest->Priority > node.Priority)
		{
			if(node.Key < dest->Key)
				Insert(dest->Left, node);
			else
				Insert(dest->Right, node);
		}
		else
		{
			Node *less = NULL, *greater = NULL;

			Split(dest, less, greater, node.Key);

			dest = new Node(node);
			dest->Left = less;
			dest->Right = greater;
		}
		dest->RefreshDescendants();
	}
	
	void Add(TItem item)
	{
		Insert(tree, Node(item));
	}

	/*TItem Get(Node* node, int index)
	{
		if(index <= Node::GetDescendantCount(node->Left))
			return Get(node->Left, index);
		else if(index == 1 + Node::GetDescendantCount(node->Left))
			return node->Key;
		else
			return Get(node->Right, index - Node::GetDescendantCount(node->Left) - 1);
	}

	TItem Get(int index)
	{
		return Get(tree, index);
	}

	int Find(bool finder(TItem item, int index))
	{
		int l = 1, r = Size();
		while(l < r)
		{
			int mid = (l+r)/2;
			if(finder(Get(mid),mid))
				r = mid;
			else
				l = mid+1;
		}
		if(l <= Size())
			return l;
		return -1;
	}

	int Size()
	{
		if(tree != NULL)
			return tree->DescendantCount;
		return 0;
	}

	void Remove(TItem item)
	{
		Node *less = NULL, *greater = NULL;
		Split(tree, less, greater, item);
		tree = Join(less, greater);
	}*/
};

void PrintNode(TreapNode<int>* node)
{
	if(node == NULL)
		return;

	PrintNode(node->Left);
	printf("%d ", node->Key);
	PrintNode(node->Right);
}

void Print(TreapSet<int>& treap)
{
	PrintNode(treap.tree);
}

struct Corridor : TreapSet<int>
{
	void DestroyRoom(int num)
	{
		Add(RestoreRoomNumber(num));
	}

	int RestoreRoomNumber(int num)
	{
		Node* cur = tree;
		int destroyedBefore = cur != NULL ? Node::GetDescendantCount(cur->Left) : 0;
				
		while(cur != NULL)
		{
			int order = cur->Key - destroyedBefore;
			
			if(num < order)
			{
				cur = cur->Left;
				if(cur != NULL)
					destroyedBefore -= 1 + Node::GetDescendantCount(cur->Right);
			}
			else if(num >= order)
			{
				cur = cur->Right;
				destroyedBefore++;

				if(cur != NULL)
					destroyedBefore += Node::GetDescendantCount(cur->Left);
			}
		}
		
		return num + destroyedBefore;
	}
};

Corridor corr;

void main()
{
#ifndef	ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	srand(time(0));
	int n,m;
	scanf("%d%d\n",&n,&m);
	for(int i = 0; i < m; i++)
	{
		char act;
		int num;

		scanf("%c %d\n",&act,&num);

		if(act == 'D')
			corr.DestroyRoom(num);
		else
			printf("%d\n", corr.RestoreRoomNumber(num));
	}
}