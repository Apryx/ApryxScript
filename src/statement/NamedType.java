package statement;

public class NamedType {
	
	private String name;
	
	public NamedType(String name){
		this.name = name;
	}
	
	@Override
	public String toString() {
		return name;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	@Override
	public boolean equals(Object arg) {
		return arg instanceof NamedType && ((NamedType)arg).getName().equals(name);
	}
}
