#include "tree.h" 

template <class T>
size_t BStree<T>::size() {
	if (root) {
		root->sizeRoot();
	}
	else return 0;
}
template <class T>
size_t BStree<T>::Root::sizeRoot() {
	return size_;
}


template <class T>
BStree<T>::Root::Root(T x) : data(x), left(nullptr), right(nullptr), size_(1) {}
template <class T>
BStree<T>::BStree(const std::initializer_list<T> & ilist) {

	for (T element : ilist) {
		Insert(element);
	}
};

template <class T>
BStree<T>::~BStree() {
	if (root != nullptr) {
		root->destroy(root);
	}
}
template <class T>
void BStree<T>::Root::destroy(Root* root) {

	if (root->left)
	{
		destroy(root->left);
	}
	if (root->right != 0)
	{
		destroy(root->right);
	}
	delete root;
	root = nullptr;
}

template <class T>
const T BStree<T>::Root::find_min(const Root* tree) {
	if (tree->left) return find_min(tree->left);
	else return tree->data;
}

template <class T>
void BStree<T>::Root::del(T x) {
	if ((x == data) && (!left)) {
		data = right->data;
		if (right->left) left = right->left; else { delete[] left; left = nullptr; --size_; }
		if (right->right) right = right->right; else { delete[] right; right = nullptr; --size_; }
		return;
	}
	if ((x == data) && (!right)) {
		data = left->data;
		if (left->right) right = left->right; else { delete[] right; right = nullptr; --size_; }
		if (left->left) left = left->left; else { delete[] left; left = nullptr; --size_; }
		return;
	}
	if (x < data) {
		if ((left->data == x) && (!(left->right)) && (!(left->left))) { delete[] left; left = nullptr; return; --size_; }
		if ((left->data == x) && (left->left) && (left->right)) { left->data = find_min(left->right); if (left->right->data != find_min(left->right)) left->right->del(find_min(left->right)); else { delete[] left->right; left->right = nullptr; --size_; } return; }
		else; left->del(x);

		return;
	}
	if (x > data) {
		if ((right->data == x) && (!(right->right)) && (!(right->left))) { delete[] right; right = nullptr; return; --size_; }
		if ((right->data == x) && (right->left) && (right->right)) { right->data = find_min(right->right); if (right->right->data != find_min(right->right)) right->right->del(find_min(right->right)); else { delete[] right->right; right->right = nullptr; --size_; } return; }
		else right->del(x);
		return;
	}
	if ((x == data) && (left) && (right)) { data = find_min(right); if (right->data != find_min(right)) right->del(find_min(right)); else { delete[]right; right = nullptr; --size_; } return; }

}

template <class T>
void BStree<T>::Root::Insert(T x) {
	if (x < data) {
		if (left != nullptr) left->Insert(x);
		if (left == nullptr) left = new Root(x);
		++size_;
	}
	if (x>data) {
		if (right != nullptr) right->Insert(x);
		if (right == nullptr) right = new Root(x);
		++size_;
	}
}
template <class T>
bool BStree<T>::Root::Search(T x) {
	if (x == data) { return true; }
	if (x > data) if (right != nullptr) return(right->Search(x));
	if (x < data) if (left != nullptr) return(left->Search(x));
	return false;
}
template <class T>
bool BStree<T>::Root::show() {
	if (this != nullptr) {
		if (left != nullptr) left->show();
		cout << data << " ";
		if (right != nullptr) right->show();
		return true;
	}
	else {

		return false;
	}
}
template <class T>
bool BStree<T>::Root::print_file(ofstream &fout) {
	if (this != nullptr) {
		if (fout.is_open()) {
			if (left != nullptr) left->print_file(fout);
			fout << data << " ";
			if (right != nullptr) right->print_file(fout);
		}
		return true;
	}
	return false;
}
template <class T>
bool BStree<T>::Insert(T x) {
	if (root != nullptr) if (Search(x)) throw Exist();
	if (root == nullptr) { root = new Root(x); return true; }
	else { root->Insert(x); return true; }
	return false;
}
template <class T>
bool BStree<T>::Search(T x) {
	if (root == nullptr) throw Empty();
	return(root->Search(x));
}
template <class T>
bool BStree<T>::del(T x) {
	if (root == nullptr) throw Empty();
	if (!this->Search(x)) { return false; }
	if (this->size() == 1) {
		root = nullptr;
		delete root;
		root = nullptr;

	}
	else {
		root->del(x);
	}
	return true;
}

template <class T>
ostream & operator <<(ostream & out, BStree<T> & tree) {
	if (tree.root->show()) return out;
	else throw Empty();
}
template <class T>
ifstream& operator >>(ifstream & fin, BStree<T> & tree) {
	if (!fin.is_open()) throw File_Not_Open();
	T x;
	while (!fin.eof()) {
		if (fin >> x) tree.Insert(x);
		else break;
	}
	return fin;
}
template <class T>
ofstream & operator <<(ofstream & fout, BStree<T> & tree) {
	if (tree.root->print_file(fout)) return fout; else throw Empty();
}

template <class T>
istream & operator >> (istream & in, BStree<T> & tree) {
	size_t size;
	if (in >> size) {
		for (int i = 0; i < size; ++i) {
			T temp;
			if (in >> temp) {
				tree.Insert(temp);
			}
			else {
				throw
					Error_stream();
			}
		}
	}
	else {
		throw Error_stream();
	}

	return in;

}

template <class T>
bool BStree<T>::operator == (const BStree<T> &tree)
{


	iterator i = begin();
	iterator j = tree.begin();
	for (; i != end() || j != tree.end(); ++i, ++j) {
		if (*i != *j) {
			return false;
		}
	}

	return true;
}


