# ĐỒ ÁN QUẢN LÝ CHUYẾN BAY

## ĐỀ BÀI

#### Máy bay:

- Mảng con trỏ có tối đa 300 máy bay
- Mỗi máy bay có các thông tin (Số hiệu MB (C15), loại máy bay (C40), số dãy, số dòng)
- Mỗi máy bay có 1 số hiệu duy nhất; (số chỗ = số dãy \* số dòng ), số chỗ >=20
  Nếu số dãy = 5 nghĩa là máy bay có các dãy A, B, C, D, E; Nếu số dòng = 20 nghĩa là máy bay có các hàng ghế được đánh số từ 1 đến 20. Kết hợp dãy và hàng ghế ta sẽ có số vé.

#### Chuyến bay:

- Danh sách liên kết đơn ( Mã CB (C15), Ngày giờ khởi hành, sân bay đến , trạng thái, Số hiệu MB, danh sách vé)
- Mỗi chuyến bay có 1 mã duy nhất; trạng thái chuyến bay bao gồm: 0: hủy chuyến, 1: còn vé, 2: hết vé,3: hoàn tất
- Danh sách vé cho biết thông tin vé trên chuyến bay, và số CMND của hành khách đã đặt vé đó
- Danh sách chuyến bay luôn có sẵn thứ tự theo mã chuyến bay

#### Hành khách:

- Cây nhị phân tìm kiếm(Số CMND, Ho, Ten, Phai)

## TÀI LIỆU

- MinGw: https://sourceforge.net/projects/mingw-w64/
- Cài đặt MinGw cho Visual Studio Code: https://code.visualstudio.com/docs/cpp/config-mingw
- Raylib (64 bit): https://github.com/raysan5/raylib/wiki/Working-on-Windows
- Hình ảnh sử dụng: Google hình ảnh
- Font chữ: Arial (C:/Windows/Fonts/arial.ttf)

## VẤN ĐỀ

- Tìm kiếm chuyến bay chi tiết theo ngày hoạt động sai cách
- Các thao tác trên giao diện có thể bị đơ (có thể khắc phục bằng đa luồng)
- file build_run.bat chưa hoàn thiện (chạy thủ công)
- Các lỗi chưa rõ

## CÁCH SỬ DỤNG

#### Cách 1: Chạy file build_run.bat

Chạy thông qua file build_run.bat, yêu cầu có sẵn MinGw trong máy

#### Cách 2: Chạy qua Visual Studio Code

Chỉ cần build (Ctrl + Shift + B) và run (F5)

#### Cách 3: Chạy thủ công

- Build: `g++ -g imp/**.cpp -o main.exe -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm`
- Run: `main.exe`

## NGƯỜI THỰC HIỆN

- Leader: Tô Phan Kiều Thương
- Thành viên: Nguyễn Lê Hoài Bắc
- Thành viên: Phạm Bùi Nam Phương
