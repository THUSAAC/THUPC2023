import math

TYPE = ['Weak', 'Average', 'Strong']
TYPE_RATE = [
  [1.0, 0.9, 1.1],
  [1.1, 1.0, 0.9],
  [0.9, 1.1, 1.0],
]
POS_RATE = [1.25, 1.00, 0.75, 0.00, 0.75, 1.00]
WE = [4, 2, 0, 1, 3, 5]

class Warrior(object):
  def __init__(self, team, id, Type):
    self.team = team
    self.id = id
    self.name = f'{team.name} {id+1}'
    self.Type = Type
    self.TypeId = TYPE.index(Type)
    self.Lv = None
    self.maxhp = None
    self.atk = None
    self.def_ = None
    self.skillLv = None
    self.passivesklLv = None
    self.weapon = None
    self.weaponatk = None
    self.skill_rate = 1
    self.debuff_rate = 0
    self.debuff_round = 0
    self.east = None
    self.west = None

  def inc_hp(self, heal):
    if self.hp == self.maxhp:
      return
    heal = int(math.floor(heal+1e-9))
    self.hp = min(self.hp + heal, self.maxhp)
    print('{} recovered +{} hp -> {}/{}'.format(self.name, heal, self.hp, self.maxhp))

  def dec_hp(self, damage, source):
    damage = int(math.floor(damage+1e-9))
    self.hp = max(self.hp - damage, 0)
    print('{} took {} damage from {} -> {}/{}'.format(self.name, damage, source, self.hp, self.maxhp))
    if self.hp == 0:
      self.team.maintain()

  def debuff(self, rate):
    self.debuff_rate = rate
    self.debuff_round = 3

  def checkout(self):
    if self.debuff_round > 0:
      self.dec_hp(self.maxhp * self.debuff_rate, 'skill')
      self.debuff_round -= 1

  def print_skill(self, target):
    print('{} applied {} skill to {}'.format(self.name, self.Type, target.name))


class Weak(Warrior):
  def __init__(self, team, id):
    super().__init__(team, id, 'Weak')

  def skill(self, target):
    SKILL = [0, 0.1, 0.12, 0.15, 0.17, 0.20]
    obj = self.team.member[target]
    self.print_skill(obj)
    obj.inc_hp(SKILL[self.skillLv] * obj.maxhp)

  def passive_skill(self):
    SKILL = [0, 0.013, 0.016, 0.019, 0.022, 0.025]
    self.team.inc_heal(SKILL[self.passivesklLv])


class Average(Warrior):
  def __init__(self, team, id):
    super().__init__(team, id, 'Average')

  def skill(self, target):
    SKILL = [0, 0.06, 0.07, 0.08, 0.09, 0.10]
    obj = self.team.rival.member[target]
    self.print_skill(obj)
    obj.debuff(SKILL[self.skillLv])

  def passive_skill(self):
    SKILL = [0, 0.01, 0.02, 0.03, 0.04, 0.05]
    self.team.inc_def(SKILL[self.passivesklLv])


class Strong(Warrior):
  def __init__(self, team, id):
    super().__init__(team, id, 'Strong')

  def skill(self, target):
    SKILL = [0, 2.1, 2.17, 2.24, 2.32, 2.4]
    obj = self.team.member[target]
    self.print_skill(obj)
    obj.skill_rate = SKILL[self.skillLv]

  def passive_skill(self):
    SKILL = [0, 0.01, 0.02, 0.03, 0.04, 0.05]
    self.team.inc_atk(SKILL[self.passivesklLv])


class Attack(object):
  def __init__(self):
    self.source = None
    self.target = None
    self.atkpos = None
    self.ddgpos = None
    self.team = None
    self.rival = None


class Basicattack(Attack):
  def __init__(self):
    super().__init__()

  @property
  def target_warrior(self):
    return self.rival.member[self.target]

  def damage(self, target: Warrior, rate):
    defense = target.def_ * self.rival.def_
    attack = self.attack * rate * TYPE_RATE[self.source.TypeId][target.TypeId]
    target.dec_hp(attack / defense, self.source.name)

  def get_attack(self):
    self.attack = self.source.atk * self.source.weaponatk * self.source.skill_rate * self.team.atk * POS_RATE[(self.atkpos - self.ddgpos) % 6]

  def trigger(self):
    self.get_attack()
    self.damage(self.target_warrior, 1)
    self.source.skill_rate = 1


def neighbor(target: Warrior):
  ret = []
  if target.west:
    ret.append(target.west)
  if target.east:
    ret.append(target.east)
  return ret

def B(target: Warrior):
  return [(target, 1.25)]

def G(target: Warrior):
  target_list = [target] + neighbor(target)
  return [(targ, 1.35 / len(target_list)) for targ in target_list]

def M(target: Warrior):
  return [(target, 1.15)] + [(targ, 0.23) for targ in neighbor(target)]

class Specialattack(Basicattack):
  def __init__(self):
    super().__init__()

  def trigger(self):
    self.get_attack()
    for target, rate in self.source.weapon(self.target_warrior):
      self.damage(target, rate)
    self.source.skill_rate = 1

class Skill(Attack):
  def __init__(self):
    super().__init__()

  def trigger(self):
    self.source.skill(self.target)


class Team(object):
  def __init__(self, name):
    self.name = name
    self.turn = 0
    self.member = []

  def find_warrior(self):
    n = len(self.member)
    for i in range(n):
      turn = (self.turn + i) % n
      if self.member[turn].hp != 0:
        self.turn = (turn + 1) % n
        return self.member[turn]
    return None

  def inc_heal(self, rate):
    self.heal = min(self.heal + rate, 0.05)

  def inc_def(self, rate):
    self.def_ = min(self.def_ + rate, 1.1)

  def inc_atk(self, rate):
    self.atk = min(self.atk + rate, 1.1)

  def maintain(self):
    self.heal = 0
    self.def_ = 1
    self.atk = 1
    self.active_member = [member for member in self.member if member.hp != 0]
    for member in self.member:
      if member.hp != 0:
        member.passive_skill()
    west = east = None
    for i in WE:
      if i < len(self.member) and self.member[i].hp != 0:
        self.member[i].west = west
        west = self.member[i]
    for i in WE[::-1]:
      if i < len(self.member) and self.member[i].hp != 0:
        self.member[i].east = east
        east = self.member[i]

  def do_heal(self):
    if self.heal != 0:
      for member in self.active_member:
        member.inc_hp(self.heal * member.maxhp)

  def do_poisoning(self):
    tmp = self.active_member
    for member in tmp:
      member.checkout()

def parse_warrior(targ, fields, name: list=[], rename: dict={}):
  idx = 0
  for field in fields:
    if field.find('=') == -1:
      key = name[idx]
      val = field
      idx += 1
    else:
      key, val = field.split('=')
      key = rename.get(key, key)
    val = eval(val)
    targ.__setattr__(key, val)

def read_team(size, name):
  team = Team(name)
  for i in range(size):
    row = input().split()
    warrior = eval(row[0])(team, i)
    parse_warrior(warrior, row[1:], ['weapon'], {'def': 'def_'})
    warrior.hp = warrior.maxhp
    team.member.append(warrior)
  return team

ATK_CLS = {
  'Basicattack' : Basicattack,
  'Specialattack' : Specialattack,
  'Skill' : Skill,
}
def read_atk():
  row = input().split()
  atk = ATK_CLS[row[0]]()
  atk.target = int(row[1][7:])
  if len(row) != 2:
    atk.atkpos = int(row[2][7:])
    atk.ddgpos = int(row[3][7:])
  return atk

def main():
  n, m = map(int, input().split())
  team = []
  team.append(read_team(n, 'South'))
  team.append(read_team(m, 'North'))
  team[0].rival = team[1]
  team[1].rival = team[0]
  team[0].maintain()
  team[1].maintain()
  T = int(input())
  for i in range(T):
    atk = read_atk()
    atkTeam = team[i % 2]
    defTeam = team[(i + 1) % 2]
    atkTeam.do_heal()
    atk.source = atkTeam.find_warrior()
    atk.team = atkTeam
    atk.rival = defTeam
    atk.target -= 1
    atk.trigger()
    defTeam.do_poisoning()
    output = ''
    for t in team[::-1]:
      output += '{}:'.format(t.name)
      for id in WE:
        if id < len(t.member):
          output += ' '
          output += str(t.member[id].hp)
          output += '/'
          output += str(t.member[id].maxhp)
      output += '\n'
    print(output)
  if team[0].find_warrior() is None:
    print('Team North won.')
  if team[1].find_warrior() is None:
    print('Team South won.')

main()
