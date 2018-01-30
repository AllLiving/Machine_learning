
struct node {
	/*
	 * something here
	 * ...
	 * ...
	 */

	/* the number of subnodes is uncertain */
	node **children;
};

node *root;
Set Data;	// the dataset
Set Attr;	// the attribute set

void init()
{
	/* intialize the root node
	 * and the dataset
	 * and the attribute set
	 * here
	 */
}

bool meet_with_bound(D, A)
{
	/* three conditions */
}

int choose_attr(D, A)
{
	if(USE_ID3)
	{
		/* ... */
	}
	else if(USE_C4_5)
	{
		/* ... */
	}
	else if(USE_CART)
	{
		/* ... */
	}
	else
	{
		/* what do you want to do? */
	}
}

vector<Set> divide_data(D, a)
{
	/* divide dataset `D` according to the attribute `a` */
}

void recursive(node *p)
{
	if(meet_with_bound(Data, Attr))
	{
		/* do something */
		return;
	}

	/* choose the best attribute */
	int attr_chosen = choose_attr(Data, Attr);

	/* 
	 * divide the current dataset into
	 * several subsets
	 * according to `attr_chosen`
	 */
	vector<Set> subsets = divide_data(Data, attr_chosen);

	/* delete the attribute which has been chosen */
	Attr.delete(attr_chosen)

	for subset in subsets do
	{
		node *subnode = new node;

		/* how connect `p->children` with `subnode`? */
		
		/* replace the current dataset with `subset` */
		swap(Data, subset);

		/* recursion */
		recursive(subnode);

		/* restore the current dataset, why? */
		swap(Data, subset);
	}

	/* 
	 * add the attribute which has just been deleted
	 * back to `Attr`, why?
	 */
	Attr.add(attr_chosen)

	return;
}
