struct Student
{
	int id;
	char* name;
};
struct StackNode
{
	Student* info;
	StackNode* next;
};
struct QueueNode
{
	Student* info;
	QueueNode* next;
};
StackNode* createStackNode(Student *s);

void pushNode(StackNode* &root, Student* s);

Student* popNode(StackNode* &root);

QueueNode* createQueueNode(Student *s);

void enqueueNode(QueueNode* &root, Student* s);

Student* dequeueNode(QueueNode* &root);

Student* createStudent(int id, char* name);