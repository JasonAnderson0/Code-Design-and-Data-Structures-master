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


      void Draw(int numb, int row)
      {
              DrawRectangle(posX * numb, posY * row, 60, 60, color);

              static char buffer[10];

              sprintf_s(buffer, "%d", data);
              DrawText(buffer, posX * numb + 10, posY * row + 10, 35, BLACK);

              if (next != nullptr)
              {
                  DrawRectangle(next->posX * numb + 60, next->posY * row + 30, 20, 5, BLACK);
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
      if (isEmpty()) return;
      auto iter = head;
      while (iter != tail) {
          if (iter->data = searchVal)
          {
              if (iter->next != nullptr && iter->prev != nullptr) 
              {
                  iter->next->prev = iter->prev;
                  iter->prev->next = iter->next;
              }
                  delete iter;

              break;
          }
          else { iter = iter->next; }
      }
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
      bool sorted;
      Node* temp;
      Node* temp2 = nullptr;

      if (head == nullptr)
          return;
      do 
      {
          sorted = 0;
          temp = head;

          while(temp->next != temp2)
          {
              if(temp->data > temp->next->data)
              {
                  std::swap(temp->data, temp->next->data);
                  sorted = 1;
              }
              temp = temp->next;
          }
          temp2 = temp;
      } while (sorted);
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

    list.PushFront(3);
    list.PushFront(8);
    list.PushFront(10);
    list.PushBack(20);

    LinkedList<int> list2;

    list2.PushFront(4);
    list2.PushFront(1);
    list2.PushFront(63);
    list2.PushFront(250);
    list2.Sort();
    int boxValue = 0;
    bool boxEdit = false;
    static char buffer[10];

    int screenWidth = 800;
    int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    float delta = GetFrameTime();

    int thirty = 30;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        int number = list.Count();
        int count = 0;

        sprintf_s(buffer, "%d", number);
        DrawText(buffer, 150, 10, 35, BLACK);
        const char nodes[] = "Nodes:";
        DrawText(nodes, 10, 10, 35, BLACK);


        for (LinkedList<int>::Node* node = list.begin(); node != nullptr; node = node->next)
        {
            if (node != nullptr) {
                count++;
                node->Draw(count, 1);
            }
        }

        count = 0;

        for (LinkedList<int>::Node* node = list2.begin(); node != nullptr; node = node->next)
        {
            if (node != nullptr) {
                count++;
                node->Draw(count, 2);

            }
        }



        EndDrawing();
    }

    CloseWindow();
    return 0;
}