코드는 총 다섯 개의 파일로 이루어져 있습니다. 
처음에는 헤더 파일 하나에 cpp 파일 하나를 대응시켜 헤더에는 선언만 하려고 했으나,
알 수 없는 이유 때문에 디버깅에 자꾸 실패하여 전부 헤더로 옮기게 되었습니다. 

main.cpp
main함수만 있습니다.
main함수에서는 Mlp class와 test Dataloader를 만들고,
 while문을 이용해 반복적으로 Mlp의 기능인 train, predict, validation, layer-visualize를 사용할 수 있도록 구현했습니다.

Dataloader.h
데이터로더 클래스가 선언되어 있습니다.
멤버 변수인 data, label에 접근하기 위한 함수 두 개를 추가로 만들었습니다.

Layer.h
Layer class가 선언되어 있습니다.
forward 함수를 train, validation, test 하나씩 만들었습니다. 각자 data 개수가 달라서 다루기 쉽도록 만들었습니다.
matmul 함수는 두 행렬과 각 행렬의 행, 열 정보를 받아 행렬곱으로 새 행렬을 만드는 함수입니다.
transpose 함수는 하나의 행렬을 받아 전치행렬을 만드는 함수입니다.
멤버 변수인 in_dimention, out_dimention에 접근하기 위한 함수 두 개를 추가로 만들었습니다.

Loss.h
Loss class가 선언되어 있습니다. 
forward 함수를 train, validation 하나씩 만들었습니다.
멤버 변수인 gradient_y에 접근하기 위한 함수를 추가로 만들었습니다.

Mlp.h
Mlp class가 선언되어 있습니다.
find_max_index 함수는 data 1개가 어느 label에 속해 있는지 판단할 때 용이하도록 하기 위해 만들었습니다.
accuracy 함수는 train_accuarcy, validation_accuarcy를 계산하기 편하게 하려고 만들었습니다.
pdf에 있는 add_layer와 read_dataset 함수는 Mlp의 생성자 내부에 구현해 두었고, 다른 곳에서 쓰일 일이 없기에 만들어 두지 않았습니다.


