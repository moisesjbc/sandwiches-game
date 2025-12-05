extends Danger

func _init():
	self.full_damage = 20


func use_tool(used_tool_type, delta):
	if used_tool_type == ToolType.HAND:
		hp = 0
		play("off")
