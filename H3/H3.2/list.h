struct list_elem {
    struct list_elem *next;	// Zeiger auf das naechste Element
    int	     *data;	// Zeiger auf ein Datenobject
};

typedef struct list {
	struct list_elem *first;// erstes Element in der Liste
	struct list_elem *last;	// letztes Element in der Liste
} list_t;

/* function prototypes */
list_t           *list_init ();
struct list_elem *list_insert (list_t *list, int *data);
struct list_elem *list_append (list_t *list, int *data);
int              list_remove (list_t *list, int *data);
void             list_finit (list_t *list);
void             list_print (list_t *list, void (*print_elem) (int *));
struct list_elem *list_find (list_t *list, int *data);
void print_int(int *data);
