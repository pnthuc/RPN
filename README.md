# RPN Calculator (Reverse Polish Notation)

Đây là một chương trình C++ thực hiện chuyển đổi biểu thức toán học từ dạng trung tố (infix) sang hậu tố (postfix hay RPN - Reverse Polish Notation) và tính giá trị biểu thức hậu tố đó.

---

## Mục tiêu

- **Chuyển đổi biểu thức trung tố thành hậu tố**
- **Đánh giá giá trị biểu thức hậu tố**
- **Xử lý các phép toán: `+`, `-`, `*`, `/` và dấu ngoặc `()`**

---

## Ý tưởng chính

### 1. Chuyển đổi Infix → Postfix

Hàm `infixToPostfix()` thực hiện:

- Duyệt từng ký tự của biểu thức.
- Sử dụng stack để lưu trữ toán tử và dấu ngoặc.
- Đưa toán hạng trực tiếp vào vector hậu tố.
- Ưu tiên toán tử dựa theo độ ưu tiên: `*/` > `+-`.
- Quản lý dấu ngoặc để đảm bảo tính đúng đắn cú pháp.

### 2. Tính biểu thức hậu tố

Hàm `evaluatePostfix()` thực hiện:

- Duyệt vector biểu thức hậu tố.
- Gặp số thì đẩy vào stack.
- Gặp toán tử thì lấy 2 phần tử từ stack, tính toán, rồi đẩy kết quả vào lại stack.
- Trả về phần tử cuối cùng còn lại trong stack là kết quả.

---

## Giải thích mã nguồn

```cpp
enum Operator { ADD, SUB, MUL, DIV };
```
Định nghĩa toán tử dưới dạng enum để dễ thao tác và đọc mã.

```cpp
int getOperatorCode(char op);
```
Chuyển ký tự `+ - * /` thành enum tương ứng.

```cpp
void infixToPostfix(const string& expr, vector<pair<bool, long long>>& postfix);
```
Chuyển biểu thức từ infix sang postfix. Vector chứa cặp:
- `first = true`: toán hạng (số)
- `first = false`: toán tử (mã enum)

```cpp
double evaluatePostfix(const vector<pair<bool, long long>>& postfix);
```
Tính toán kết quả biểu thức hậu tố.

```cpp
void printPostfix(const vector<pair<bool, long long>>& postfix);
```
In biểu thức hậu tố ra màn hình.

```cpp
int main();
```
Chạy thử một loạt các biểu thức mẫu, in ra:
- Biểu thức gốc (infix)
- Biểu thức hậu tố
- Kết quả tính toán

---

## Ví dụ kết quả

```
Infix: 3+4*(2-1)/5
Postfix: 3 4 2 1 - * 5 / +
Result: 3.8
-----------------------------
```

---

## Xử lý lỗi

Chương trình có thể phát hiện và thông báo các lỗi sau:

- Sai cú pháp dấu ngoặc
- Biểu thức không hợp lệ
- Phép chia cho 0

---

## Yêu cầu biên dịch

Chạy bằng trình biên dịch C++11 trở lên:

```bash
g++ -std=c++11 -o rpn main.cpp
./rpn
```

---


## Ghi chú

- Hiện tại chỉ hỗ trợ 4 phép toán `+`, `-`, `*`, `/`.
