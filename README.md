# Project: MindList


---

## Commit Rule
Base Rule : [gitmoji](https://gitmoji.dev/) <br>
Other Rule : 개인적으로 규칙을 정의함.<br>
Coding Style : [Google-StyleGuid-Cpp](https://google.github.io/styleguide/cppguide.html)<br>
Other Style : Google Style Guid를 준수하되, 아직 파악하지 못 한 가이드는 개인 스타일로 코드를 작성함.<br>


### Gitmoji
🎉(tada): 프로젝트 시작<br>
✨(sparkles) : 새 기능 추가<br>
🚀(rocket) : 성능 개선<br>
🔧(wrench) : 구성 파일 추가 / 업데이트<br>
🔨(hammer) : 개발 스크립트 추가 / 업데이트<br>
🔥(fire) : 코드 / 파일 삭제<br>
💩(poop) : 안 좋은 코드(개선 필요)<br>
💡(bulb) : 주석 작성<br>
🩹(adhesive_bandage) : 간단한 수정(크리티컬 이슈X)<br>
🚚(truck) : 파일 / 경로 / 이름 변경<br>
⚰️(coffin) : 죽은 코드 삭제<br>
🐛(bug) : 버그 수정<br>
♻️(recycle) : 리팩토링<br>
📝(memo) : 문서 추가 / 업데이트<br>
💄(lipstick) : UI 개선<br>
📦(package) : 컴파일된 파일 추가<br>

### Commit Title
Create : 새 파일이나 프로젝트를 생성할 때<br>
Add : 새 기능이나 파일을 추가할 때<br>
Delete : 파일이나 기능을 삭제할 때<br>
Update : 기능을 개선하거나 중요한 변경을 할 때(=최신화)<br>
Modify : 기존 기능의 작은 수정이나 리팩토링할 때(=작은 단위 수정)<br>
Fix : 버그 수정을 할 때<br>

### Commit Message
변경된 사항에 대한 간략한 메시지를 남깁니다.<br>

### Commit File
to (FileName).c : 새로운 함수를 파일에 추가한 경우<br>
in (FileName).c : 특정 함수 내의 로직을 수정한 경우<br>


### Commit Format

(Gitmoji) (Commit Title) (Commit Message) (Commit File)

### Others

gitmoji를 우선으로 작성하고, Commit Title에 할당된 gitmoji는 달라도 됨.<br>
Example Case #1: Update Script -> 🔧 Update system in main.c<br>

기능 수정 범위:<br> 
Modify(소규모) < Update(대규모, 최신화)<br>
기능 수정의 규모가 작으면 Modify를, 규모가 크면 Update를 사용하기.<br>
Update는 **최신화**의 의미를 가지고 있으므로, README.md 파일과 같이 최신화 작업을 시켜줄 때는 Udate Title을 사용하기.<br>
규모에 따라 Title이 다르므로, 리팩토링 시 규모에 따라 Modify 혹은 Update 중 하나를 선택하기<br>