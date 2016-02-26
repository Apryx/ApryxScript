package statement;

public class NameAndType {
	private String name;
	private String type;
	
	public NameAndType(String name, String type){
		this.name = name;
		this.type = type;
	}
	
	public String getType() {
		return type;
	}
	
	public String getName() {
		return name;
	}
	
	@Override
	public String toString() {
		return name + ":" + type;
	}
	
}
