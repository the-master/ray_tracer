#include <string.h>
#include <stdlib.h>

#if !defined(equals_)
#error equals_(a,b) needs to be defined so contains and remove_all will work
#endif // !equals_

#if defined(type_)


#define insert__ insert_
#define new_arraylist__ new_arraylist_
#define arraylist__ arraylist_
#define contains__ contains_
#define remove__ remove_
#define index_of__ index_of_
#define remove_all__ remove_all_
#define delete__ delete_

#define ccat(a,b) ccat2(a,b)
#define ccat2(a,b) a##b
#define insert_ ccat(insert__,type_)
#define new_arraylist_ ccat(new_arraylist__,type_)
#define arraylist_ ccat(arraylist__,type_)
#define contains_ ccat(contains__,type_)
#define remove_ ccat(remove__,type_)
#define index_of_ ccat(index_of__,type_)
#define remove_all_ ccat(remove_all__,type_)
#define delete_ ccat(delete__,ccat(type_,arraylist__))


#if defined(header_)
typedef struct arraylist_{
	type_* content;
	int n;
	int allocated_;
	int (*insert)(struct arraylist_* list, int index, type_  val);
	int	(*index_of)(struct arraylist_* list, type_ val);
	type_( *remove)(struct arraylist_* list, int i);
	int ( *remove_all)(struct arraylist_* list, type_ val);
	int ( *contains)(struct arraylist_* list, type_ val);
	void ( *del)(struct arraylist_* list);

}arraylist_;
int insert_(arraylist_ * list, int index, type_  val);
int index_of_(arraylist_* list, type_ val);
type_ remove_(arraylist_* list, int i);
int remove_all_(arraylist_* list, type_ val);
void delete_(arraylist_* list);
int contains_(arraylist_* list, type_ val);
arraylist_ new_arraylist_();
#else
arraylist_ new_arraylist_() {
	return (arraylist_) 
	{
		.n = 0,
		.allocated_=0,
		.content = malloc(0),
		.insert = insert_,
		.index_of = index_of_,
		.remove = remove_,
		.remove_all = remove_all_,
		.contains = contains_,
		.del = delete_
	};

}

//index <0			=> prepend
//index > list->n	=> append
int insert_(arraylist_* list, int index,type_  val) {

	index = index > list->n ? list->n : index;
	index = index < 0 ? 0 : index;
	list->n++;
	if (list->n > list->allocated_) {
		type_* temp = realloc(list->content, sizeof(type_) * list->n * 2);
		if (temp == 0) {
			list->n--;
			return 0;
		}		
		
		list->content = temp;
		list->allocated_ = list->n*2;
	}
	if (index == 0)
		memmove(list->content + index + 1, list->content + index, (list->n - index - 1) * sizeof(type_));

	list->content[index] = val;
	return 1;
}

int index_of_(arraylist_* list, type_ val) {
	for (int i = 0; i < list->n; i++)
		if (equals_(list->content[i], val))
			return i;
	return -1;
}
/*index i*/
type_ remove_(arraylist_* list, int i) {
	type_ rv = (type_){ 0 }; 
	if (i >= 0 && i < list->n) {
		rv = list->content[i];
		memmove(list->content + i, list->content + i + 1, (list->n - i) * sizeof(type_));
		list->n--;
	}
	return rv;

}
/*value val*/
int remove_all_(arraylist_* list, type_ val) {
	int count = 0;
	for (int i = index_of_(list, val); i != -1; i = index_of_(list, val)) {
		remove_(list, i);
		count++;
	}
	return count;
}

void delete_(arraylist_* list) {
	free(list->content);
	*list = (arraylist_){ 0 };
}

int contains_(arraylist_* list, type_ val) {
	for (int i = 0; i < list->n; i++)
		if (equals_(list->content[i], val))
			return 1;
	return 0;
}
#endif// header

#else
#error define type_ set_ insert_ new_arraylist_ and arraylist_
#endif // type

#undef type_
#undef equals_


#undef insert__
#undef new_arraylist__
#undef arraylist__
#undef contains__
#undef remove__
#undef index_of__
#undef remove_all__
#undef delete__

#undef ccat
#undef ccat2

#undef insert_
#undef new_arraylist_
#undef arraylist_
#undef contains_
#undef remove_
#undef index_of_
#undef remove_all_
#undef delete_