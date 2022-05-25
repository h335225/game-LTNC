# Báo cáo bài tập lớn môn Lập trình nâng cao
- Họ và tên: Nguyễn Thị Hồng Hạnh 
- MSSV: 21020016
- Game: EverWing

# 1. Cách lấy và chạy chương trình (dành cho hệ điều hành Window):
- Bước 1: Download file everWing.rar trên github và MinGW-W64 tại https://sourceforge.net/projects/mingw-w64/
- Bước 2: set up MinGW-W64: 
  - Giải nén file x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z. 
  - Copy thư mục `mingw64` vào **<ROOTDIR>** (Ví dụ `D:\software`). 
  - Cài đặt đường dẫn PATH đến **<ROOTDIR>\mingw64\bin**. Kiểm tra bằng cách gọi g++ và mingw32-make trong terminal
- Bước 3: Giải nén, tìm và chạy file EverWing.exe để chạy game.
  
# 2. Mô tả chung về trò chơi, các ý tưởng chính:
- Di chuyển tiên bằng chuột và bắn quái vật.
- Khi va phải quái vật sẽ bị trừ lượng mạng nhất định. Đồng thời sẽ xuất hiện vòng bảo vệ tiên khỏi bị tấn công trong vài giây.
- Ăn xu để khi hết mạng có thể đổi xu lấy mạng. Xu chỉ có tác dụng trong lúc chơi, không tích lũy khi thoát game
- Sau khi chơi 1 thời gian thì boss sẽ xuất hiện. Khi bắn chết boss lớn thì 2 boss con sẽ xuất hiện. 
- Khi tiêu diệt được boss thì bạn thắng.
  
# 3. Mô tả các chức năng đã cài đặt
Video minh họa: https://youtu.be/2NpLqLxc1Gw

Mô tả:
- Tại menu có nút **play** và **exit** để chơi và thoát game
- Trong khi chơi nếu người chơi ấn nút thoát (nút x) hoặc bấm 'q' thì sẽ có phần hỏi người chơi muốn thoát hay không.
- Khi hết mạng mà người chơi đã thu thập ít nhất 20xu thì game sẽ hỏi có muốn đổi 20 xu lấy 1 mạng hay không.
- Có âm thanh lúc bắn và thu thập xu và mạng. Âm thanh boss kêu.
- Chơi càng lâu thì số quái vật càng tăng lên đến số lượng nhất định thì dừng lại.
- Hiển thị thanh máu của người chơi và quái vật.
  
# 4. Các kỹ thuật lập trình được sử dụng trong chương trình:
Các kỹ thuật lập trình:
  
- Sử dụng các kiến thức cơ bản đã được dạy như mảng, xâu (string), hàm rand()...
- Sử dụng biến const, con trỏ và tham chiếu.
- Sử dụng class, struct,...
  
  
Với thư viện SDL2, SD2_image, SDL2_mixer, SDL2_ttf
- Xử lí sự kiện chuột, bàn phím.
- Sử dụng hàm trong các thư viện để tạo hình ảnh, âm thanh, chữ cho game.

# 5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình:
# Kết luận và điều tâm đắc
- Chú trọng cách đặt tên biến và hàm để hiểu và khi cần có thể tìm dễ dàng.
- Chia file để dễ quản lý hơn.
- Sử dụng nhiều ngôn ngữ hay thư viện để code dễ dàng hơn.

# Hướng phát triển game
- Thêm chuyển động cho đối tượng trong game để game sinh động hơn.
- Thêm boss với các cách tấn công khác nhau
- Thêm nhiều màn chơi
- Có thể chơi lại
- Tích trữ xu để đổi vật phẩm hoặc nâng cấp sức mạnh.
