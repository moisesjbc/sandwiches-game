extends CharacterBody2D

@onready var current_tool = null
@onready var current_tool_type = null
var current_danger = false


func _ready():
	Input.set_mouse_mode(Input.MOUSE_MODE_HIDDEN)
	set_current_tool(ToolType.HAND)


func is_one_hit_tool(tool_type):
	return tool_type in [ToolType.HAND, ToolType.GAVEL]
	

func _process(delta):
	global_position = get_global_mouse_position()
	if current_danger and not is_one_hit_tool(current_tool_type) and current_tool.animation == "on":
		current_danger.use_tool(current_tool_type, delta)


func set_current_tool(new_tool_type):
	if current_tool:
		current_tool.visible = false
		current_tool.get_node("audio").stop()

	if new_tool_type == ToolType.HAND:
		current_tool = $hand
	elif new_tool_type == ToolType.EXTINGUISHER:
		current_tool = $extinguisher
	elif new_tool_type == ToolType.LIGHTER:
		current_tool = $lighter
	elif new_tool_type == ToolType.GAVEL:
		current_tool = $gavel

	current_tool_type = new_tool_type
	current_tool.visible = true
	
	current_tool.play("off")


func _input(event):
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT:
		if event.pressed:
			current_tool.play("on")
			current_tool.get_node("audio").play()
			
			if current_danger and is_one_hit_tool(current_tool_type):
				current_danger.use_tool(current_tool_type, 0)
		else:
			current_tool.play("off")
			current_tool.get_node("audio").stop()
