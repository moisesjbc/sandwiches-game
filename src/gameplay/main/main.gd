extends Node2D


var player_hp: int = 100


func _ready():
	$gui.set_health(player_hp)


func apply_damage(damage):
	player_hp -= damage
	$gui.set_health(player_hp)
	if player_hp <= 0:
		Callable(get_tree(), "reload_current_scene").call_deferred()
