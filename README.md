# Crypt of the Necrodancer 모작

- 개발 기간 : 2023.02.14 ~ 2023.05.08
- 스택 : C++ , WinAPI
- 개발인원 : 1
- 대상 플랫폼 : Windows

# 📜프로젝트 설명

이 프로젝트는 Window API와 게임 엔진에 대해 공부하기 위해 만든 Crypt of the Necrodancer 모작입니다. 
**Crypt of the Necrodancer**는 **Brace Yourself Games**에서 만든 로그라이크 리듬 던전 크롤러입니다. 

로그라이크의 랜덤 던전 생성과 몬스터의 행동 패턴 개발에 집중하기 위해 해당 게임을 선택했습니다.

### 링크

- 소개 영상: https://youtu.be/2EQH4TvCqfU
- 깃허브: https://github.com/Luci-Park/CryptOfTheNecrodancer
- 노션 : https://www.notion.so/park-spring-note/Crypt-of-the-Necrodancer-d5223f5f23da4fe884cf9cbd8c31fa47

---

# ❗역할

단독 프로젝트였습니다. 에셋을 마련하고 게임의 메커니즘을 연구하고 구현하는 **Reverse Engineering 과정**을 진행하였습니다.

### 핵심

- 매 판 랜덤으로 생성되는 던전
    본 게임에서 각 던전은 대부분 6개의 방이 각각 하나의 복도로 연결되어 있는 일직선의 형태를 이루고 있었습니다. 그래서 다음과 같은 방식으로 구현했습니다.
  
  1. DFS로 방들을 직선으로 하되 자리가 없을 경우 전 방에서 자리를 찾도록 구현
  2. 방의 형태와 크기를 랜덤으로 생성
     1. 첫 방은 중간 보스가 있는 출구 방으로
        1. 이때 첫 방은 맵의 왼쪽 혹은 아래쪽에 생성
     2. 5번째 방은 시작 방으로
     3. 그 외는 랜덤 방으로
  3. 첫 방이 아니라면 전 방에 대해 상하좌우 방향 중에 들어갈 수 있는 위치에 방을 배치
  4. 만약 상하좌우 중 그 어떤 방향에도 삽입이 안된다면 그 전 방으로 돌아가서 3번 반복
  5. 두 방을 잇는 복도 생성
  6. 방이 6개가 되거나 맵에 자리가 없을 때까지 반복

[자세한 코드](https://github.com/Luci-Park/CryptOfTheNecrodancer/blob/1080c0501670b84d2b619cda25ca03a44dda6d89/Client/LRandomMap.cpp#L54)

- 박자에 따른 움직임
    플레이어는 매 박자마다 움직일 수 있습니다. 앞 뒤로 반 박자 정도의 오차로 입력이 가능합니다. 모든 몬스터는 플레이어가 움직이거나 움직임 없이 박자가 지나갔을 때 행동 합니다.
    이를 위해 박자를 계산하는 **지휘자**와 플레이어의 입력이 박자에 맞는지 확인 하는 **심판** 클래스를 두었습니다. 또한 움직임이 끝나면 몬스터들이 움직일 수 있게 알리는 것을 **observer 패턴**을 통해 구현했습니다.

[지휘자 코드](https://github.com/Luci-Park/CryptOfTheNecrodancer/blob/1080c0501670b84d2b619cda25ca03a44dda6d89/Client/LConductor.cpp#L36)

- 빛 시스템
  
  - 본 게임과 동일하게 게임 내 타일 당 빛은 다음 법칙에 따라 계산됩니다.
    1. 타일이 밝혀지려면 **충분한 빛** + **플레이어의 시야**가 필요
    2. 밝혀지지 않는 타일은 보이지 않게 유지
    3. 충분한 빛은 광원의 최대 빛의 30%를 지칭
    4. 모든 광원은 바깥 지름과 안쪽 지름으로 구성
    5. 안쪽 지름 내 타일들에는 최대 빛 밝기를 제공
    6. 안쪽 지름과 바깥 지름 사이의 타일들에는 보간된 밝기를 제공
    7. 바깥 지름 사이의 타일들에는 밝기를 미제공
  - 타일이 시야 내에 있는지에 대한 여부는 브레젠험 직선 알고리즘을 사용해서 계산했습니다.
  
  [시선 처리 코드](https://github.com/Luci-Park/CryptOfTheNecrodancer/blob/1080c0501670b84d2b619cda25ca03a44dda6d89/Client/LTileLight.cpp#L28)
  
  [빛 법칙](https://github.com/Luci-Park/CryptOfTheNecrodancer/blob/1080c0501670b84d2b619cda25ca03a44dda6d89/Client/LLightSource.cpp#L24)
  
  

---

# 💭감상

### 배운 점

- 리듬 게임 구현 시 주의점
    **노래와 게임 요소들의 타이밍을 맞추기 위해 시간이 아니라 박자 중심으로 가야 합니다.** 처음에는 모든 요소들이 각자 시간을 재서 움직이는 방식으로 했으나 따로따로 노는 문제가 있었습니다. 박자를 계산하는 클래스를 하나 두고 모든 게임 요소들은 해당 클래스로부터 타이밍을 받도록 변경하여 싱크로를 맞췄습니다.
    또한 박자에 따라 움직이는 경우 시작점과 끝점에 대해 현재 박자에 따라 선형 보간하여 위치하게 하는 것이 싱크로를 맞추는 방법입니다.

- Strategy Pattern 사용 필요 시점
    게임 내 기본 바닥으로 쓰이는 GroundTile은 여러 요소에 따라 행동 패턴이 달라집니다.  Strategy 패턴을 사용하니 유연한 행동 교체가 가능해졌습니다.
  
  [Floor Tile](https://github.com/Luci-Park/CryptOfTheNecrodancer/blob/1080c0501670b84d2b619cda25ca03a44dda6d89/Client/LFloorTile.cpp#L142) [Floor Strategy](https://github.com/Luci-Park/CryptOfTheNecrodancer/blob/a1477863c1228d8406dbb4e1270674650f8764b8/Client/LFloorStrategy.cpp)

![TileActivity](https://github.com/Luci-Park/CryptOfTheNecrodancer/assets/97658764/2fa978c1-7880-49b6-ac2c-5a1917337a0a)

### 느낀 점

Crypt of the Necrodancer 모작을 하며 저는 복잡한 게임 개발 과정에 빠져드는 즐거운 경험을 했습니다. 리듬 게임 구현에 대한 지식을 얻거나 랜덤 던전 생성 알고리즘을 개발하였습니다. 본 게임을 분석하며 다양한 도전에 직면했고, 이를 해결하는 과정이 흥미로웠습니다. **전반적으로, 모작을 통해 게임 개발, 프로그래밍, 그리고 문제 해결에 대한 실질적인 전문 지식을 얻게 해줬습니다.**


