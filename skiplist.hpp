
#ifndef _SkipList_H
#define _SkipList_H
#include <stdlib.h>
#include<iostream>
#include<vector>
#include <climits>
#include<cstdlib>
#include<ctime>


class skiplist
{
	public:
		skiplist(int szint = 10)
		{
			min = new node(INT_MIN);
			max = new node(INT_MAX);
			this->szint = szint;
			for (int i = 0; i < szint; ++i)
			{
				min->kov.push_back(max);
				max->kov.push_back(NULL);
			}
		}

		int size()
		{
			return s;
		}

		bool contains(int k)
		{
			std::vector<node*> v = magikus(k);
			return v[0]->kov[0]->adat == k;
		}

		void insert(int k)
		{
			std::vector<node*> v = magikus(k);
			if (v[0]->kov[0]->adat != k)
			{
				node* n = new node(k);
				int szint = 0;
				int r;
				do
				{
					n->kov.push_back(v[szint]->kov[szint]);
					v[szint]->kov[szint] = n;
					r = rand() % 2;
					++szint;
				} while (r > 0 && szint < this->szint);
				++s;
			}
		}

		void erase(int k)
		{
			std::vector<node*> v = magikus(k);
			if (v[0]->kov[0]->adat == k)
			{
				node* n = v[0]->kov[0];
				for (int szint = 0; szint < n->kov.size(); ++szint)
					v[szint]->kov[szint] = n->kov[szint];
				--s;
				delete n;
			}
		}


		void kiir()
		{
			std::cout << "size:" << s << std::endl;
			for (int szint = 0; szint < this->szint; ++szint)
			{
				for (node* akt = min->kov[szint]; akt != max; akt = akt->kov[szint])
				{
					std::cout << akt->adat << " ";
				}
				std::cout << std::endl;
			}
		}

	private:

		struct node
		{
			int adat;
			std::vector<node*> kov;

			node(int adat)
			{
				this->adat = adat;
			}


		};

		node* min;
		node* max;
		int szint;
		int s=0;

		std::vector<node*> magikus(int k)
		{
			std::vector<node*> v(this->szint);
			int szint = this->szint - 1;

			node* akt = min;
			while (szint >= 0)
			{
				while (akt != max && akt->kov[szint]->adat<k)
				{
					akt = akt->kov[szint];
				}
				v[szint] = akt;
				--szint;
			}
			return v;
		}

};

#endif

