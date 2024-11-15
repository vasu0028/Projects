//
// This file was generated by the Eclipse Implementation of JAXB, v2.3.5 
// See https://eclipse-ee4j.github.io/jaxb-ri 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2024.04.08 at 12:44:39 PM CDT 
//


package PlantDataClasses;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for harvest complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="harvest"&gt;
 *   &lt;complexContent&gt;
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType"&gt;
 *       &lt;sequence&gt;
 *         &lt;element name="amount" type="{http://www.w3.org/2001/XMLSchema}integer"/&gt;
 *         &lt;element name="cropValue" type="{http://www.w3.org/2001/XMLSchema}integer"/&gt;
 *         &lt;element name="xp" type="{http://www.w3.org/2001/XMLSchema}integer"/&gt;
 *         &lt;element name="isDestroyed" type="{http://www.w3.org/2001/XMLSchema}boolean"/&gt;
 *         &lt;element name="fallBackStage" type="{http://www.w3.org/2001/XMLSchema}integer"/&gt;
 *         &lt;element name="sprite" type="{http://www.w3.org/2001/XMLSchema}string"/&gt;
 *       &lt;/sequence&gt;
 *     &lt;/restriction&gt;
 *   &lt;/complexContent&gt;
 * &lt;/complexType&gt;
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "harvest", propOrder = {
    "amount",
    "cropValue",
    "xp",
    "isDestroyed",
    "fallBackStage",
    "sprite"
})
public class Harvest {

    @XmlElement(required = true)
    protected int amount;
    @XmlElement(required = true)
    protected int cropValue;
    @XmlElement(required = true)
    protected int xp;
    protected boolean isDestroyed;
    @XmlElement(required = true)
    protected int fallBackStage;
    @XmlElement(required = true)
    protected String sprite;

    /**
     * Gets the value of the amount property.
     * 
     * @return
     *     possible object is
     *     {@link int }
     *     
     */
    public int getAmount() {
        return amount;
    }

    /**
     * Sets the value of the amount property.
     * 
     * @param value
     *     allowed object is
     *     {@link int }
     *     
     */
    public void setAmount(int value) {
        this.amount = value;
    }

    /**
     * Gets the value of the cropValue property.
     * 
     * @return
     *     possible object is
     *     {@link int }
     *     
     */
    public int getCropValue() {
        return cropValue;
    }

    /**
     * Sets the value of the cropValue property.
     * 
     * @param value
     *     allowed object is
     *     {@link int }
     *     
     */
    public void setCropValue(int value) {
        this.cropValue = value;
    }

    /**
     * Gets the value of the xp property.
     * 
     * @return
     *     possible object is
     *     {@link int }
     *     
     */
    public int getXp() {
        return xp;
    }

    /**
     * Sets the value of the xp property.
     * 
     * @param value
     *     allowed object is
     *     {@link int }
     *     
     */
    public void setXp(int value) {
        this.xp = value;
    }

    /**
     * Gets the value of the isDestroyed property.
     * 
     */
    public boolean isIsDestroyed() {
        return isDestroyed;
    }

    /**
     * Sets the value of the isDestroyed property.
     * 
     */
    public void setIsDestroyed(boolean value) {
        this.isDestroyed = value;
    }

    /**
     * Gets the value of the fallBackStage property.
     * 
     * @return
     *     possible object is
     *     {@link int }
     *     
     */
    public int getFallBackStage() {
        return fallBackStage;
    }

    /**
     * Sets the value of the fallBackStage property.
     * 
     * @param value
     *     allowed object is
     *     {@link int }
     *     
     */
    public void setFallBackStage(int value) {
        this.fallBackStage = value;
    }

    /**
     * Gets the value of the sprite property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSprite() {
        return sprite;
    }

    /**
     * Sets the value of the sprite property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSprite(String value) {
        this.sprite = value;
    }

}
