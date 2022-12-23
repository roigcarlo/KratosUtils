from base import BaseStage

class LitterClass1:
    def __init__(self):
        print("I am a magnificent class that someone may be tempted to implement here becuase of reasons.")

class LitterClass2:
    def __init__(self):
        print("I am a horripilant class that someone may be tempted to implement here becuase of reasons.")

class UserStage1(BaseStage):
    def __init__(self):
        super().__init__()
        print("I am a User Stage 1 (From BaseStage)")