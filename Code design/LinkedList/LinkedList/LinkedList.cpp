#include <iostream>
#include <algorithm>
#include "raylib.h"



template <typename T>
class LinkedList
{
 public:

    struct Node 
    {
    public:
      T data;
      Node* prev{ nullptr };
      Node* next{ nullptr };
      Color color = YELLOW;
      int posX = 80;
      int posY = 80;


      void Draw(int numb)
      {
          DrawRectangle(posX * numb,posY, 60, 60, color);



          if (next != nullptr)
          {
              DrawRectangle(next->posX * numb + 60, next->posY + 30, 20, 5, BLACK);
          }
      }
    };


  ~LinkedList() 
  {
      for(Node* node = head; node != nullptr;)
      {
          Node* next = node->next;
          delete node;
          node = next;
      }
  }

  //List nullptr <->Node1 <-> Node2 <-> nullptr

  bool isEmpty() { return (head == nullptr && tail==nullptr); }

  void PushFront(const T& value)
  {
      Node* temp = new Node{ value };
      if (head) 
      {
          temp->next = head;
          head->prev = temp;
      }
      if (tail == nullptr) tail = temp;
      head = temp;
  }

  void PushBack(const T& value)
  {
      Node* temp = new Node{ value };
      if (tail) 
      {
          tail->next = temp;
          temp->prev = tail;
      }
      if (head == nullptr) head = temp;
      tail = temp;
  }

  void Insert(T value,T searchedVal)
  {
      Node* temp = new Node{ value };
      auto iter = head;
      while (iter != tail) {
          if (iter->data = searchedVal) 
          {
              iter->next->prev = temp;
              temp->next = iter->next;
              iter->next = temp;
              temp->prev = iter;
              break;
          }
          else { iter = iter->next; }
      }

  }

  void popFront()
  {
      if (isEmpty())return;
      Node* temp = head->next;
      if (temp) temp->prev = nullptr;
      delete head;
      head = temp;

      if (isEmpty()) return;
  }

  void popBack()
  {
      if (isEmpty())return;
      Node* temp = tail->prev;
      if (temp) temp->next = nullptr;
      delete tail;
      tail = temp;
  }

  void popLocation(T& searchVal)
  {
      

  }

  int Count() 
  {
      int count = 0;
      auto iter = head;
      while(iter != nullptr)
      {
          iter = iter->next;
          count++;
      }
      return count;
  }

  void Sort()
  {
      int swapped, i;
      Node* ptr1;
      Node* ptr = nullptr;

      if (head == nullptr)
          return;
      do 
      {
          swapped = 0;
          ptr1 = head;

          while(ptr1->next != ptr)
          {
              if(ptr1->data > ptr1->next->data)
              {
                  std::swap(ptr1->data, ptr1->next->data);
                  swapped = 1;
              }
              ptr1 = ptr1->next;
          }
          ptr = ptr1;
      } while (swapped);


  }

  Node* begin() {return head;}
  Node* end() { return tail; }


private:
     Node* head{ nullptr };
     Node* tail{ nullptr };


};

int main()
{
    LinkedList<int> list;

    list.PushFront(10);
    list.PushFront(3);
    list.PushFront(8);
    list.PushBack(20);

    LinkedList<int> list2 = list;
    list2.PushFront(88);
    list2.Sort();
    int boxValue = 0;
    bool boxEdit = false;
    static char buffer[10];

    int screenWidth = 800;
    int screenHeight = 550;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    float delta = GetFrameTime();

    while (!WindowShouldClose()) 
    {


        BeginDrawing();
        ClearBackground(WHITE);


        int number = list.Count();
        int count = 0;
        for (LinkedList<int>::Node* node = list2.begin(); node != nullptr; node = node->next)
        {
            count++;
            node->Draw(count);

            sprintf_s(buffer, "%d", node->data);
            DrawText(buffer, node->posX * count + 10, node->posY + 10, 35, BLACK);
        }

        sprintf_s(buffer, "%d", number);
        DrawText(buffer, 150, 10, 35, BLACK);
        const char nodes[] = "Nodes:";
        DrawText(nodes, 10, 10, 35, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}