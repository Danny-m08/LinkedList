/*	Daniel Marquez
	COP4530
	FSU Computer Science */    

//--------------------------const_iterator class--------------------------------

template<typename T>
List<T>::const_iterator::const_iterator( ) : current{ nullptr } {}

template<typename T>
const T& List<T>::const_iterator::operator* ( ) const{
	 return retrieve( ); 
	}

template<typename T>
typename List<T>::const_iterator &
List<T>::const_iterator::operator++ ( ){
        current = current->next;
        return *this;
    	}

template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator++ ( int ){
        const_iterator temp = *this;
        ++( *this );
        return temp;
	}

template<typename T>
typename List<T>::const_iterator &
List<T>::const_iterator::operator--(){
	current = current ->prev;
	return *this;
	}

template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator--(int){
	const_iterator temp = *this;
	--( *this);
	return temp;
	}

template<typename T>
bool List<T>::const_iterator::operator== ( const const_iterator & rhs ) const{
	return current == rhs.current; 
	}

template <typename T>
bool List<T>::const_iterator::operator!= ( const const_iterator & rhs ) const{ 
	return current != rhs.current; 
	}

template <typename T>
T& List<T>::const_iterator::retrieve( ) const{
	return current->data; 
	}

template<typename T>
List<T>::const_iterator::const_iterator( Node *p ) : current{ p } {}





//---------------------------------template
template<typename T>
List<T>::iterator::iterator(){}

template<typename T>
T& List<T>::iterator::operator*(){ 
	return const_iterator::retrieve();
	}
template<typename T>
const T& List<T>::iterator::operator*()const{
	return const_iterator::operator*();
	}

template<typename T>
typename List<T>::iterator &
List<T>::iterator::operator++(){
	this->current = this->current -> next;
	return *this;
	}

template<typename T>
typename List<T>::iterator
List<T>::iterator::operator++(int){
	iterator temp = *this;
	++(*this);
	return temp;
	}

template <typename T>
typename List<T>::iterator &
List<T>::iterator::operator--(){
	this->current = this->current ->prev;
	return *this;
	}

template <typename T>
typename List<T>::iterator
List<T>::iterator::operator--(int){
	iterator temp{this};
	--(*this);
	return temp;
	}

template <typename T>
List<T>::iterator::iterator(Node *p):const_iterator{p}{}


/*----------------------List Class------------------------------------
--------------------------------------------------------------------*/


template<typename T>		//works
void List<T>::init(){
	theSize = 0;
	head = new Node;
	tail = new Node;
	head ->next = tail;
	tail ->prev = head;
	}

template<typename T>		//works
List<T>::List(){
	init();
	}

template<typename T>		//works
List<T>::~List(){
	clear();
	delete head;
	delete tail;
	}
template<typename T>
List<T>::List(const List &rhs ){//works
	init();
	for(auto &x: rhs){
		push_back( x );
		}
	}

template<typename T>
const List<T> & List<T>::operator=(const List &rhs){
	List temp = rhs;	//works
	swap(*this, temp);
	return *this;
	}

template<typename T>
List<T>::List(List && rhs):theSize{rhs.theSize},head{rhs.head},tail{rhs.tail}{
	rhs.theSize = 0;	//works
	rhs.head = nullptr;
	rhs.tail = nullptr;
	}

template<typename T>
List<T>::List(int num, const T& val){
	init();
	for(int i = 0 ; i < num; i++) push_front(val);
	}
template<typename T>
List<T>::List(const_iterator start, const_iterator end){
	init();
	for(const_iterator it2 = start; it2 != end;  ++it2){
		push_back(*it2);
		}
	}

template<typename T>
List<T> & List<T>::operator=( List && rhs){
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
	}

template<typename T>
int List<T>::size()const{
	return theSize;
	}

template<typename T>
bool List<T>::empty()const{
	return theSize == 0;
	}

template<typename T>		//works
void List<T>::clear(){
	if(!empty()){
		erase(begin(), end());
		}
	/*	for(iterator it = begin(); it != end();){
			it = erase(it);}
		theSize = 0;
		}*/
	}

template<typename T>
void List<T>::reverse(){		//works
	List<T> temp = *this;
	erase(begin(), end());
	//std::cout<< *this<< std::endl;
	for(iterator it = temp.begin(); it != temp.end();++it){
		this->push_front(*it);
		}	
	//std::cout<< "reverse: " << *this<< std::endl;
	}

template<typename T>			//works
T & List<T>::front(){
	return *begin();
	}

template<typename T>			//works
const T & List<T>::front()const{
	return *begin();
	}

template<typename T>			//works
T & List<T>::back(){
	return *(--end());
	}

template<typename T>			//works
const T & List<T>::back()const{
	return *(--end());
	}
	

template<typename T>
void List<T>::push_front(const T & val){
	insert( --begin(), val);	//works
	}

template<typename T>
void List<T>::push_front(T && val){	//works
	insert( --begin(), std::move(val) );
}

template<typename T>			//works
void List<T>::push_back(const T &val){
	insert( --end(), val);}


template<typename T>			//works
void List<T>::push_back(T && val){
	insert(--end(), val);}

template<typename T>			//works
void List<T>::pop_front(){
	if(!empty()){
		erase(begin());
		}
	}
	
template<typename T>			//works
void List<T>::pop_back(){
	if(!empty()){
		erase(--end());
		}
	}

template<typename T>
void List<T>::remove(const T &val){	//works
	for(iterator it = begin(); it != end();++it){
		if(*it == val){
			erase(it);}
		}
	}

template<typename T>			//works
void List<T>::print(std::ostream& os,char ofc)const{
	for(auto it = begin(); it != end(); it++){
		os << *it << ofc;
		}
	}

template<typename T>
typename List<T>::iterator
List<T>::begin(){				//works
	iterator it{ head->next};
	return it;}

template<typename T>
typename List<T>::const_iterator		//works
List<T>:: begin() const{
	typename List<T>::const_iterator it{ head->next };
	return it;
	}

template<typename T>
typename List<T>::iterator
List<T>::end(){					//works
	iterator it{tail};
	return it;}

template<typename T>
typename List<T>::const_iterator 
List<T>::end() const{				//works
	const_iterator it{tail};
	return it;}

template<typename T>
typename List<T>::iterator		//works
List<T>::insert(iterator itr, const T& val){
	if(itr != end()){
		Node *p = (++itr).current;
		theSize++;
		Node * newNode = new List<T>::Node{ val, p->prev, p};
		p->prev = p->prev->next = newNode;
		iterator temp{newNode};
		return temp;	
		}
	return itr;
	}

template<typename T>		//works
typename List<T>::iterator
List<T>::insert(iterator itr, T && val){
	if(itr != end() ){
	 Node*p = (++itr).current;
	 theSize++;
         Node *newNode = new Node{std::move(val),p->prev, p};
	 p->prev = p->prev->next = newNode;
	 iterator temp{newNode};
	 return temp;}
	return itr;
	}

template<typename T>			//Works
typename List<T>::iterator
List<T>::erase(iterator itr){
	Node *p = itr.current;
	iterator temp {p->next};
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	theSize--;
	
	return temp;
	}

template<typename T>
typename List<T>::iterator			//Works
List<T>::erase(iterator start, iterator end){
	iterator temp{start.current};
	for(; temp != end;){
		temp = erase(temp);}
	return temp;
	}

template <typename T>				//works
bool operator==(const List<T> & lhs, const List<T> &rhs){
	typename List<T>::const_iterator it1 = lhs.begin(), it2 = rhs.begin();
	if( lhs.size() != rhs.size() ) return false;
	for(; it1 != lhs.end(); ++it1,++it2){
		if(*it1 != *it2) return false;}
	return true;
	}

template <typename T>				//works
bool operator!=(const List<T> & lhs, const List<T> &rhs){
	return !(lhs == rhs);}

template <typename T>				//works
std::ostream & operator<<(std::ostream &os, const List<T> &l){
	l.print(os);
 	return os;
	}
