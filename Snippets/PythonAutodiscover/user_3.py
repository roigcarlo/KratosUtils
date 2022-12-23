from user_2 import UserStage2

class UserStage3(UserStage2):
    def __init__(self):
        super().__init__()
        print("I am a User Stage 3 (From UserStage2)")