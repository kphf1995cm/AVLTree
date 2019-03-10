/*
 *	@Func: An implementation of AVLTree in c++
 *	@Author: kuangpeng kp18@mails.tsinghua.edu.cn
 *	@Time: 2017
 */

# include<iostream>
# include<time.h>
# include"avl.h"
# include<math.h>
using namespace std;
template<class T, class K>
class AVL
{
private:
	AVLnode<T, K>*root;
	void LL(AVLnode<T, K>*pt, AVLnode<T, K>*cur, AVLnode<T, K>*last)
	{
		if (pt->p != NULL)
		{
			if (pt->p->lc == pt) pt->p->lc = cur;
			else pt->p->rc = cur;
			cur->p = pt->p;
		}
		else
		{
			root = cur;
			cur->p = NULL;
		}
		pt->lc = cur->rc;
		if(cur->rc) cur->rc->p = pt;
		cur->rc = pt;
		pt->p = cur;
	}

	void LR(AVLnode<T, K>*pt, AVLnode<T, K>*cur, AVLnode<T, K>*last)
	{
		if (pt->p != NULL)
		{
			if (pt->p->lc == pt) pt->p->lc = last;
			else pt->p->rc = last;
			last->p = pt->p;
		}
		else
		{
			root = last;
			last->p = NULL;
		}
		pt->lc = last->rc;
		if(last->rc) last->rc->p = pt;
		last->rc = pt;
		pt->p = last;
		cur->rc = last->lc;
		if(last->lc) last->lc->p = cur;
		last->lc = cur;
		cur->p = last;
	}

	void RR(AVLnode<T, K>*pt, AVLnode<T, K>*cur, AVLnode<T, K>*last)
	{
		if (pt->p != NULL)
		{
			if (pt->p->lc == pt) pt->p->lc = cur;
			else pt->p->rc = cur;
			cur->p = pt->p;
		}
		else
		{
			root = cur;
			cur->p = NULL;
		}
		pt->rc = cur->lc;
		if(cur->lc) cur->lc->p = pt;
		cur->lc = pt;
		pt->p = cur;
	}

	void RL(AVLnode<T, K>*pt, AVLnode<T, K>*cur, AVLnode<T, K>*last)
	{
		if (pt->p != NULL)
		{
			if (pt->p->lc == pt) pt->p->lc = last;
			else pt->p->rc = last;
			last->p = pt->p;
		}
		else
		{
			root = last;
			last->p = NULL;
		}
		cur->lc = last->rc;
		if (last->rc) last->rc->p = cur;
		last->rc = cur;
		cur->p = last;
		pt->rc = last->lc;
		if (last->lc) last->lc->p = pt;
		last->lc = pt;
		pt->p = last;
	}

	int mymax(int a, int b)
	{
		return a > b ? a : b;
	}


	void changeBF(AVLnode<T, K>*r)
	{
		if (r != NULL)
		{
			r->balanceFactor = abs(getHeight(r->lc)-getHeight(r->rc));
			changeBF(r->lc);
			changeBF(r->rc);
		}
	}

	int getchangeBF(AVLnode<T, K>*p)
	{
		if (p)
		{
			return abs(getHeight(p->lc) - getHeight(p->rc));
		}
		else return 0;
	}

	AVLnode<T, K>* getMinnode(AVLnode<T, K>* p)
	{
		AVLnode<T, K>*parent=p;
		while (p)
		{
			parent = p;
			p = p->lc;
		}
		return parent;
	}

	void rotate(int i, int j, AVLnode<T, K>*pt, AVLnode<T, K>*cur, AVLnode<T, K>*last)
	{
		if (i == 0 && j == 0) LL(pt, cur, last);
		else
		{
			if (i == 0 && j == 1) LR(pt, cur, last);
			else
			{
				if (i == 1 && j == 0) RL(pt, cur, last);
				else RR(pt, cur, last);
			}
		}
	}
public:
	AVL()
	{
		root = NULL;
	}
	AVLnode<T, K>* find(AVLnode<T,K>*r,T t, K k = 0)
	{
		if (r == NULL) return NULL;
		if (r->data == t&&r->key == k) return r;
		else
		{
			if (t < r->data) return find(r->lc, t, k);
			else return find(r->rc, t, k);
		}
	}
	int getHeight(AVLnode<T, K>*r)
	{
		if (r == NULL) return 0;
		return (mymax(getHeight(r->lc), getHeight(r->rc)) + 1);
	}
	void insert(T t, K k = 0);
	void remove(AVLnode<T, K>*deletenode);
	void inorder_traverse(AVLnode<T, K>*r)
	{
		if (r != NULL)
		{

			inorder_traverse(r->lc);
			cout << r->data << " ";
			inorder_traverse(r->rc);
		}
	}
	void preorder_traverse(AVLnode<T, K>*r)
	{
		if (r != NULL)
		{
			cout << r->data << " ";
			preorder_traverse(r->lc);
			preorder_traverse(r->rc);
		}
	}
	void preorder_bf_traverse(AVLnode<T, K>*r)
	{
		if (r != NULL)
		{
			cout << r->balanceFactor<< " ";
			preorder_bf_traverse(r->lc);
			preorder_bf_traverse(r->rc);
		}
	}
	AVLnode<T, K>* getRoot()
	{
		return root;
	}
	void deletenode(T t, K k = 0)
	{
		AVLnode<T, K>*temp = find(root,t, k);
		remove(temp);
	}
	int getLevel(AVLnode<T, K>* r)
	{
		if (r != NULL)
		{
			if (r->p == NULL) return 0;
			else return 1 + getLevel(r->p);
		}
		else return -1;
	}
	void printAVL(AVLnode<T, K>*p, int level)
	{
		if (p != NULL)
		{
			printAVL(p->rc, level + 1);
			for (int i = 0; i < level; i++)
			{
				cout << "    ";
			}
			cout << p->data << endl;
			printAVL(p->lc, level + 1);
		}

	}
};
template<class T,class K>
void AVL<T, K>::insert(T t, K k = 0)
{
	if (find(root,t, k) == NULL)
	{
		AVLnode<T, K>* temp = new AVLnode<T, K>(t, k);
		AVLnode<T, K>*r = root;
		AVLnode<T, K>*parent = NULL;
		stack<int> S;
		if (root == NULL) root = temp;//先将该节点插入
		else
		{
			while (r)
			{
				parent = r;
				if (t < r->data) r = r->lc;
				else r = r->rc;
			}
			if (t < parent->data) parent->lc = temp;
			else parent->rc = temp;
			temp->p = parent;
		}
		AVLnode<T, K>*tpo = temp;
		//int flag = 0;
		while (tpo)
		{
			if (tpo->balanceFactor == 1 && getchangeBF(tpo)>1)
			{
				//flag = 1;
				break;
			}
			if (tpo->p)
			{
				if (tpo->p->lc == tpo) S.push(0);//左偏放0
				else S.push(1);
			}
			tpo = tpo->p;
		}
		AVLnode<T, K>*pt, *cur, *last;
		if (tpo!=NULL)
		{
			pt = tpo;
			int i, j;
			i = S.pop();
			if (i == 0) cur = tpo->lc;
			else cur = tpo->rc;
			tpo = cur;
			j = S.pop();
			if (j == 0) last = tpo->lc;
			else last = tpo->rc;
			rotate(i, j, pt, cur, last);
		}
		changeBF(root);
	}
}

template<class T,class K>
void AVL<T, K>::remove(AVLnode<T, K>*deletenode)
{
	if (deletenode != NULL)
	{
		AVLnode<T, K>*dlc = deletenode->lc, *drc = deletenode->rc;
		if (deletenode->lc == NULL)
		{
			if (deletenode->p)
			{
				if (deletenode->p->lc == deletenode) deletenode->p->lc = deletenode->rc;
				else deletenode->p->rc = deletenode->rc;
				if (deletenode->rc) deletenode->rc->p = deletenode->p;
			}
			else 
			{
				root = deletenode->rc;
				if(deletenode->rc) deletenode->rc->p = NULL;
			}
		}
		else
		{
			if (deletenode->rc == NULL)
			{
				if (deletenode->p)
				{
					if (deletenode->p->lc == deletenode) deletenode->p->lc = deletenode->lc;
					else deletenode->p->rc = deletenode->lc;
					deletenode->lc->p = deletenode->p;
				}
				else
				{
					root = deletenode->lc;
					deletenode->lc->p = NULL;
				}
			}
			else
			{
				AVLnode<T, K>* minnode = getMinnode(deletenode->rc);
				deletenode->data = minnode->data;
				deletenode->key = minnode->key;
				remove(minnode);
			}
		}
		if (dlc == NULL || drc == NULL)
		{
			changeBF(root);
			AVLnode<T, K>* tempnode = deletenode->p;
			while (tempnode)
			{
				if (tempnode->balanceFactor > 1)
				{
					AVLnode<T, K>*pt = tempnode, *cur, *last;
					int i, j;
					if (getHeight(tempnode->lc) - getHeight(tempnode->rc) > 0)
					{
						i = 0;
						cur = tempnode->lc;
						if (getHeight(cur->lc)>getHeight(cur->rc)) { j = 0; last = cur->lc; }
						else { j = 1; last = cur->rc; }
					}
					else
					{
						i = 1;
						cur = tempnode->rc;
						if (getHeight(cur->lc)>getHeight(cur->rc)) { j = 0; last = cur->lc; }
						else { j = 1; last = cur->rc; }
					}
					rotate(i, j, pt, cur, last);
					changeBF(root);
				}
				tempnode = tempnode->p;
			}
			delete deletenode;
		}
	}

}
void test()
{
  srand(unsigned(time(NULL)));
  AVL<int, int> avltree;
  int const N = 30;
  int t;
  int a[] = { 1,3,3,3,4 };
  for (int i = 0; i < N; i++)
  {
	  t = rand() % 50;
	  avltree.insert(t);
  }
  avltree.printAVL(avltree.getRoot(), avltree.getLevel(avltree.getRoot())); 
}
void main()
{
	test();
}