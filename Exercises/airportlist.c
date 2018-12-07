// AIRPORTLIST.C [180924]
// Code to manage a linked list of airport codes.  See exercise 1 for details
// of the question

#include	<stdio.h>


// Airport codes are three letters long.  Held in a string, an airport code
// requires 4 bytes.
typedef char AirportCode[4];

// Use a typedef to create a name for our node type
typedef struct _node  Node, *pNode;

// Define actual structure for the nodes
struct _node {
	Node		*pnext;		// pointer to next node in list
	AirportCode	Airport;	// actual airport code
	};
#define	Nodesize	(sizeof (struct _node))

Node	*headA;

void printlist (Node *plist)
// Print contents of the list.  Basically, walk through list, printing
// airport codes as we go.
{
	int   donefirst = 0;   // you'll see why in a moment
	if (plist == NULL)	{
		printf ("<EMPTY LIST>\n");
		return;
		}
	while (plist != NULL)    {
		// after the first one, print an arrow before the next one
        if (!donefirst)	{
			donefirst = 1;
		} else	{
			printf ("->");
			}
		printf ("%s", plist->Airport);
		plist = plist->pnext;
		}
	printf ("\n");
}//print()


void copycode (char *src, char *dst)
{
	printf ("Setting up node with code  %s\n", src);
	if (src != NULL)
		while (*src != '\0')	*dst++ = *src++;
	*dst = '\0';
}
		

Node *createnode (char *pcode)
// Create a new node, initializing the airport code from string pointed
// to by pcode
{
	Node	*ptmp;
	ptmp = (Node *) malloc (Nodesize);
	if (ptmp != NULL)	{
		copycode (pcode, ptmp->Airport);
		}
	return ptmp;
}
		
		

int InsertFront (Node **pl, Node *pnode)
// Insert node pointed to by pnode into existing list pointed to by
// pl.
// Returns 0 if OK, -1 if an error occurred
{
	Node	*ptmp;			// temporary pointer to list

	if (pl == NULL || pnode == NULL)	return -1;
	ptmp = *pl;				// get head pointer
	pnode->pnext = ptmp;	// new node points to existing list
	*pl = pnode;			// make head pointer point to new first node
	return 0;
}


Node *DeleteFront (Node **pl)
// Removes first node from list
{
	Node	*ptmp;

	if (pl == NULL)	return NULL;
	ptmp = *pl;				// get head pointer
	if (ptmp == NULL)	{
		// empty list
		return NULL;
		}
	*pl = ptmp->pnext;		// first node uncoupled; head ptr now
							// points to previous second in list
	return ptmp;
}


void main (void)
{
	Node	*ptmp;

	headA = NULL;
	printlist (headA);
	ptmp = createnode ("YYZ");
	InsertFront (&headA, ptmp);
	ptmp = createnode ("YUL");
	InsertFront (&headA, ptmp);
	ptmp = createnode ("LAX");
	InsertFront (&headA, ptmp);
	printlist (headA);
	ptmp = DeleteFront (&headA);
	printf ("Removed node %s\n", ptmp->Airport);
	free (ptmp);
	printlist (headA);
}



