[Observable collection bind to specific item (by property value)](https://stackoverflow.com/questions/45818244/observable-collection-bind-to-specific-item-by-property-value)

[Binding a WPF ComboBox to ObservableCollection](https://learn.microsoft.com/en-us/answers/questions/843515/binding-a-wpf-combobox-to-observablecollection.html)

```xaml
     <ComboBox ItemsSource="{Binding Path=CountryEntries}"
               DisplayMemberPath="Country"
               SelectedValuePath="Country"
               SelectedValue="{Binding Path=CountryValue}"
               SelectedItem="{Binding Path=SelectedCountry}"/>
```

🌟 [Difference between SelectedItem, SelectedValue and SelectedValuePath](https://stackoverflow.com/questions/4902039/difference-between-selecteditem-selectedvalue-and-selectedvaluepath)

[Selector.SelectedValuePath Property](https://learn.microsoft.com/en-us/dotnet/api/system.windows.controls.primitives.selector.selectedvaluepath)

```xaml
<XmlDataProvider x:Key="Employees" XPath="/Employees/*">
  <x:XData>
    <Employees xmlns="">
      <Employee Name="Terry Adams" Type="FTE" EmployeeNumber="1" />
      <Employee Name="Claire O'Donnell" Type="FTE" EmployeeNumber="12345" />
      <Employee Name="Palle Peterson" Type="FTE" EmployeeNumber="5678" />
      <Employee Name="Amy E. Alberts" Type="CSG" EmployeeNumber="99222" />
      <Employee Name="Stefan Hesse" Type="Vendor" EmployeeNumber="-" />
    </Employees>
  </x:XData>
</XmlDataProvider>

<DataTemplate x:Key="EmployeeItemTemplate">
  <TextBlock Text="{Binding XPath=@Name}" />
</DataTemplate>
```

##### Popup

- PlacementTarget

  - [RelativeSource binding from a ToolTip or ContextMenu](https://stackoverflow.com/questions/3668654/relativesource-binding-from-a-tooltip-or-contextmenu)

  - [ElementName Binding from MenuItem in ContextMenu](https://stackoverflow.com/questions/1013558/elementname-binding-from-menuitem-in-contextmenu)
