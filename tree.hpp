#include <iostream> 
#include <fstream> 
#include <list> 
using namespace std;

template <class T>
class BStree;
template <class T>
ostream & operator<< (std::ostream & out, BStree<T> &tree);

template <class T>
ofstream & operator<< (std::ofstream & fout, BStree<T> &tree);

template <class T>
ifstream & operator >> (std::ifstream & fin, BStree<T> &tree);

template <class T>
istream & operator >> (std::istream & in, BStree<T> &tree);

template <class T>
class BStree {
public:
	

	BStree() :root(nullptr) {};
	BStree(const T  ilist);
	~BStree();
	bool operator == (const BStree<T> & tree);
	bool Insert(const T x);// 
	bool Search(const T x);// 
	bool del(T x); //
	size_t size();
	friend ostream & operator<< <>(ostream &out, BStree<T> &tree);
	friend ofstream & operator<< <>(ofstream &fout, BStree<T> &tree);
	friend ifstream & operator>> <>(ifstream &fin, BStree<T> &tree);
	friend istream & operator >> <>(istream & in, BStree<T> &tree);
	class Root;
	Root* root; //

	
	
};
template <class T>
class BStree<T>::Root {
public:
	Root(T x);
	void destroy(Root* root);
	void Insert(const T x);
	bool Search(const T x);
	size_t size_;
	size_t sizeRoot();
	bool show();
	bool print_file(ofstream &fout);
	void del(T el);
	const T get_data() { return data; };
	T data;
	Root *left;
	Root *right;
private:

};
