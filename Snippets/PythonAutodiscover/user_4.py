from user_2 import UserStage2

class UserStage4a(UserStage2):
    def __init__(self):
        super().__init__()
        print("I am a User Stage 4a (From UserStage2). Incorrect, as 2 classes are being defined here")

class UserStage4b(UserStage2):
    def __init__(self):
        super().__init__()
        print("I am a User Stage 4b (From UserStage2). Incorrect, as 2 classes are being defined here")