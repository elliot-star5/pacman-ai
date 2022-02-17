#define errExit(msg) do { \
  perror(msg); exit(EXIT_FAILURE); } while(0)

struct node
{
  int dest;
  struct node *next;
};

struct Edge
{
  int src, dest;
};
 
// graph datastructure 
typedef struct {
  // total number of vertices
  // for a graph
  size_t vertices;

  struct node** graph_head;     // head of graph
} Graph;


// Create a new graph with 
// size nodes
Graph* createGraph(size_t size)
{
  Graph* newGraph = malloc(sizeof(Graph));
  if (!newGraph)
    errExit("malloc");

  // set all the nodes initially to NULL
  newGraph->graph_head = calloc(size * sizeof(struct node *));
  if (!newGraph->graph_head)
    errExit("malloc");

  newGraph->vertices = size;
  return newGraph;
}

struct node *
createNode(void)
{
  newNode = malloc(sizeof(struct node));
  if (newNode == NULL)
    errExit("malloc");

  return newNode;
}

void 
addEdge(Graph* graph, struct Edge *edge)
{
  // create new edge at src
  newNode = createNode();
  newNode->next = graph->graph_head[edge->src];
  graph->graph_head[edge->src] = newNode;

  // create new edge at dest
  newNode = createNode();
  newNode->next = graph->graph_head[edge->dest];
  graph->graph_head[edge->dest] = newNode;
}

// initialize graph nodes with
// edges src and destination
void 
init_graph_edges(Graph* graph, struct Edge edges[], unsigned size)
{
  unsigned i;
  struct node *newNode;

  for (i = 0; i < size; i++)
    addEdge(graph, &edges[i]);
}

void 
freeGraph(Graph* graph)
{
  unsigned i;
  struct node *tmp, *cpy;

  // free all the node of graph
  for (i = 0; i < graph->vertices; i++)
  {
    tmp = graph->graph_head[i];
    while (tmp != NULL)
    {
      cpy = tmp->next;
      free(tmp);

      tmp = cpy;
    }
  }

  // free the Graph
  free(graph->graph_head);
  free(graph);
}


