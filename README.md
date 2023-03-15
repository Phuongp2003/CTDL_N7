#T4, ??? 15/03/2023
--------
    -File task và launch giờ đã chạy toàn cục
    -Dòng 23 file launch.json dùng để build và chạy cùng 1 lúc, tắt comment để dùng

#CN, ??? 12/03/2023
--------
    -Cập nhật map mới:
    main
    |
    |---.vscode
    |     |
    |     |-tasks.json - build file exe
    |     |
    |     |-launch.json - chạy file exe cùng debugger
    |
    |--header
    |     |            
    |     |-libs.h         
    |     |-dohoa.h
    |     |-chuyenbay.h    
    |     |-maybay.h       
    |     |-hanhkhach.h    
    |     |-ngaythang.h    
    |     |-header.h       
    |     |-raylib.h       
    |
    |--imp - các file thục thi
    |     |                 
    |     |-dohoa.cpp
    |     |-chuyenbay.cpp    
    |     |-maybay.cpp       
    |     |-hanhkhach.cpp    
    |     |-ngaythang.cpp         
    |
    |--lib
    |     |-libraylib.a - flag -lraylib để nhận thư viện raylib tĩnh

    -Map buildfile không thay đổi
    main
    |
    libs.h
    |
    |-dohoa.h       |
    |-dohoa.h       |
    |-chuyenbay.h   |--header.h|
    |-maybay.h      |          |-raylib.h
    |-hanhkhach.h   |
    |-ngaythang.h   |



#T6, 8h00 03/02/2003
--------

    -Chuyển next sang class ChuyenBay

    -Chuyển các hàm thực thi sang file cpp (chuyenbay.h, ngaythang.h)

    -bản mẫu hàm setDSVeMB (chưa test)
