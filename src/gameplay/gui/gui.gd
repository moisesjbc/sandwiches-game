extends Node

var current_tool_index = 0
var tool

func _ready():
	select_tool(ToolType.HAND, 0)

func set_health(health: int):
	$gui/margin_container/hbox_container/health_texture/health_label.text = "%03d" % health

func select_tool(selected_tool_type, selected_tool_index: int) -> void:
	$tool.set_current_tool(selected_tool_type)
	
	$gui/hbox_container.get_child(current_tool_index).disabled = false
	$gui/hbox_container.get_child(selected_tool_index).disabled = true
	
	current_tool_index = selected_tool_index

func _on_hand_button_pressed() -> void:
	select_tool(ToolType.HAND, 0)

func _on_extinguisher_button_pressed() -> void:
	select_tool(ToolType.EXTINGUISHER, 1)

func _on_lighter_button_pressed() -> void:
	select_tool(ToolType.LIGHTER, 2)

func _on_gavel_button_pressed() -> void:
	select_tool(ToolType.GAVEL, 3)

func _process(delta: float):
	if Input.is_action_just_pressed("tool_hand"):
		select_tool(ToolType.HAND, 0)
	elif Input.is_action_just_pressed("tool_extinguisher"):
		select_tool(ToolType.EXTINGUISHER, 1)
	elif Input.is_action_just_pressed("tool_lighter"):
		select_tool(ToolType.LIGHTER, 2)
	elif Input.is_action_just_pressed("tool_gavel"):
		select_tool(ToolType.GAVEL, 3)
